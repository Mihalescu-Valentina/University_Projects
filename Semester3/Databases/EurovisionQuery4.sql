create or alter procedure addToTables(@tableName varchar(50)) as
	if @tableName not in (select TABLE_NAME from Eurovision.INFORMATION_SCHEMA.TABLES) begin
		print 'The table is not in the database eurovision!'
		return
	end

	if @tableName in (select Name from Tables) begin
		print 'Table is already in Tables!'
		return
	end

	insert into Tables(Name) values(@tableName)
GO


create or alter procedure addToViews(@viewName varchar(50)) as
	if @viewName not in (select TABLE_NAME from Eurovision.INFORMATION_SCHEMA.VIEWS) begin
		print 'Table not present in the Eurovision database'
		return
	end
	
	if @viewName in (select Name from Views) begin
		print 'View already present in views'
		return
	end
	insert into Views(Name) values (@viewName)
GO

create or alter procedure addToTests (@testName varchar(50)) as
    if @testName in (select Name from Tests) begin
        print 'Test already present in Tests'
        return
    end
    insert into Tests (Name) values (@testName)
GO




--procedure that connects a Table to a Test by adding the test id and table id in the TestTables table
--it checks that the order of running the tests is properly chosen
create or alter procedure connectTableToTest (@tableName varchar(50), @testName varchar(50), @rows int, @pos int) as
    if @tableName not in (select Name from Tables) begin
        print 'Table not present in Tables'
        return
    end
    if @testName not in (select Name from Tests) begin
        print 'Tests not present in Tests'
        return
    end
    if exists(
        select *
        from TestTables T1 join Tests T2 on T1.TestID = T2.TestID
        where T2.Name=@testName and Position=@pos
        ) begin
        print 'Position provided conflicts with previous positions'
        return
    end
    insert into TestTables (TestID, TableID, NoOfRows, Position) values (
        (select Tests.TestID from Tests where Name=@testName),
        (select Tables.TableID from Tables where Name=@tableName),
        @rows,
        @pos
    )
	GO



create or alter procedure connectViewToTest (@viewName varchar(50), @testName varchar(50)) as
    if @viewName not in (select Name from Views) begin
        print 'View not present in Views'
        return
    end
    if @testName not in (select Name from Tests) begin
        print 'Tests not present in Tests'
        return
    end
    insert into TestViews (TestID, ViewID) values (
        (select Tests.TestID from Tests where Name=@testName),
        (select Views.ViewID from Views where Name=@viewName)
    )



create or alter procedure runTest (@testName varchar(50)) as
    if @testName not in (select Name from Tests) begin
        print 'test not in Tests'
        return
    end
    declare @command varchar(100)
    declare @testStartTime datetime2
    declare @startTime datetime2
    declare @endTime datetime2
    declare @table varchar(50)
    declare @rows int
    declare @pos int
    declare @view varchar(50)
    declare @testId int
    select @testId=TestID from Tests where Name=@testName
	declare @testRunId int

	set @testRunId = (select max(TestRunID)+1 from TestRuns)
    if @testRunId is null
        set @testRunId = 0
    
	
	

    --we define a cursor that scrolls through the following information:
	--for the current test we select the table names on which we perform it,no of rows inserted during testing and the pos representing the order number in which we execute the test
	declare tableCursor cursor for
        select T1.Name, T2.NoOfRows, T2.Position
        from Tables T1 join TestTables T2 on T1.TableID = T2.TableID
        where T2.TestID = @testId
        order by T2.Position desc

    --we define a cursor that goes through the views attached to/corresponding to the current test having the id @testId
	declare viewCursor cursor for
        select V.Name
        from Views V join TestViews TV on V.ViewID = TV.ViewID
        where TV.TestID = @testId

    
	--the variable that stores the start time of all the operations in the current test is set properly 
	set @testStartTime = sysdatetime()
    
    --using the tableCursor we go through all the tables we will run the current test on in order to perform the first part of the testing phase which is 
	--deleting the records from the tables
	open tableCursor
	fetch tableCursor into @table, @rows, @pos
    while @@FETCH_STATUS = 0 begin
        exec ('delete from '+ @table)
        fetch tableCursor into @table, @rows, @pos
    end
    close tableCursor

	print 'dsadasdasdasdsadasdasd';

    open tableCursor
	--we safely insert the first information in the TestRuns table(without EndAt)
    SET IDENTITY_INSERT TestRuns ON
    insert into TestRuns (TestRunID, Description, StartAt)values (@testRunId, 'Tests results for: ' + @testName, @testStartTime)
    SET IDENTITY_INSERT TestRuns OFF

	--using the tableCursor we go through all the tables we will run the current test on in order to perform the second part of the testing phase which is 
	--inserting data into test T’s tables in reverse deletion order(the reverse part is performed using last and prior) 
	--the procedure's name that inserts data into test T's tables begins with 'populateTable' 
    fetch tableCursor into @table, @rows, @pos
    while @@FETCH_STATUS = 0 begin
        set @command = 'populateTable' + @table
        if @command not in (select ROUTINE_NAME from INFORMATION_SCHEMA.ROUTINES) begin
            print @command + 'does not exist'
            return
        end
        --the variable that stores the start time of the insert operation performed during the second part of the current test is set properly 
		set @startTime = sysdatetime()
		
		--executing the second part of the test
        exec @command @rows

        --the variable that stores the end time of the insert operation performed during the second part of the current test is set properly 
		set @endTime = sysdatetime()
       
	   --inserting data into TestRunTables 
		insert into TestRunTables (TestRunID, TableId, StartAt, EndAt) values (@testRunId, (select TableID from Tables where Name=@table), @startTime, @endTime)
        fetch tableCursor into @table, @rows, @pos
    end
    close tableCursor
    deallocate tableCursor

    --using the tableCursor we go through all the tables we will run the current test on in order to perform the third part of the testing phase which is 
	--evaluating the views of the current test by using a select statement on the data from the views 
	open viewCursor
    fetch viewCursor into @view
    while @@FETCH_STATUS = 0 begin
        set @command = 'select * from ' + @view
		
		--the variable that stores the start time of the select operation performed during the third part of the current test is set properly 
		set @startTime = sysdatetime()
        exec (@command)
        
		set @endTime = sysdatetime()

        --inserting data into TestRunViews
		insert into TestRunViews (TestRunID, ViewID, StartAt, EndAt) values (@testRunId, (select ViewID from Views where Name=@view), @startTime, @endTime)
        fetch viewCursor into @view
    end
    close viewCursor
    deallocate viewCursor

    --completing the TestRuns table with the final information which is the ending time of all the operations in the current test 
	update TestRuns
    set EndAt=sysdatetime()
    where TestRunID = @testRunId

    
	
--creating the first test that is performed on a table having a single-column primary key and no foreign keys(SpokePerson)
--this first test also has a view that selects the data of the spoke persons that also were previous Eurovision contestants
exec addToTables 'SpokePerson'

create or alter view isSpokePersonPreviousContestant as
    select * from SpokePerson Sp
	where Sp.previous_contestant = 'yes'


exec addToViews 'isSpokePersonPreviousContestant'
exec addToTests 'test1'
exec connectTableToTest 'SpokePerson', 'test1', 78, 1
exec connectViewToTest 'isSpokePersonPreviousContestant', 'test1'

create or alter procedure populateTableSpokePerson (@rows int) as
    while @rows > 0 begin
        if @rows % 2 = 0
			insert into SpokePerson(sp_id, sp_name, job, place_of_report,previous_contestant) values (@rows,CONVERT(varchar(255), NEWID()),CONVERT(varchar(255), NEWID()),CONVERT(varchar(255), NEWID()),'yes')
        if @rows % 2 = 1
						insert into SpokePerson(sp_id, sp_name, job, place_of_report,previous_contestant) values (@rows,CONVERT(varchar(255), NEWID()),CONVERT(varchar(255), NEWID()),CONVERT(varchar(255), NEWID()),'no')
		set @rows = @rows-1
    end

GO

execute runTest 'test1'

delete from TestViews
delete from TestRunViews
delete from TestRuns
delete from TestRunTables
delete from SpokePerson where sp_id not in (80,81,82,83,84,85)
select * from SpokePerson









