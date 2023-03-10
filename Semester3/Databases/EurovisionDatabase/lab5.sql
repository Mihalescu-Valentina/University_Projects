CREATE TABLE Resident(
	r_id INT PRIMARY KEY,
	r_age INT UNIQUE,
	r_adress int
	
);

CREATE TABLE Town(
	t_id INT PRIMARY KEY,
	town_quality_factor INT,
	t_name VARCHAR(50),
);

CREATE TABLE Country(
	c_id INT PRIMARY KEY,
	r_id INT FOREIGN KEY REFERENCES Resident(r_id),
	t_id INT FOREIGN KEY REFERENCES Town(t_id),

	 
);


create or alter procedure populateResident(@rows int) as
	declare  @age int
	set @age = @rows*2+100
	while @rows>0 begin
		insert into Resident values(@rows,@age,@rows%120)
		set @rows = @rows -1
		set @age = @age - 2
	end


create or alter procedure populateTown(@rows int) as
	while @rows > 0 begin
		insert into Town values (@rows, @rows % 40,CONVERT(varchar(255), NEWID()))
		set @rows = @rows - 1
	end
	
create or alter procedure populateCountry(@rows int) as
	declare @rid int
    declare @tid int
    while @rows > 0 begin
        set @rid = (select top 1 r_id from Resident order by r_id asc)
        set @tid = (select top 1 t_id from Town order by t_id desc)
        insert into Country values (@rows, @rid, @tid)
        set @rows = @rows-1
    end

exec populateResident 10000
exec populateTown 12000
exec populateCountry 4000

--a

-- Clustered Index Scan
--this is a clustered index scan because the data pages include all the columns of the table Resident and we have no condition/selection of the columns
-- Cost : 0.0328005 
select * from Resident

-- Clustered Index Seek
--this is a clustered index seek because the data pages include all the columns of the table Resident and we have a where clause that selects only the columns with resident id 1
-- Cost: 0.0032831
select * from Resident where r_id = 1 

--Nonclustered Index Scan
--this is a nonclustered index scan because the data pages include only the r_age field of the table Resident and we have no filter applied on the data
-- Cost: 0.0268746
select r_age from Resident R order by r_age  

 -- Nonclustered Index Seek
 --this is a nonclustered index seek because the data pages include only the r_age field of the table Resident and we have filtered the table by age using a where clause
 -- Cost: 0.0032831
select r_age from Resident where r_age = 1 

-- Key Lookup
--this is a key lookup because the data pages include only the r_adress field of the table Resident and we have filtered the table by another column from Resident(r_age) using a where clause
-- Cost: 0.0032831
select r_adress from Resident where r_age  = 108 

--b
-- Cost before applying the nonclustered seek index - 0.0787042 
select * from Town where town_quality_factor = 12

create nonclustered index Town_qualityFactor_index on Town(town_quality_factor) include (t_id, t_name)
drop index Town_qualityFactor_index on Town

--Cost after applying the nonclustered seek index  - 0.0043173

--c
GO
CREATE OR ALTER VIEW Join1 AS
	SELECT R.r_id, T.t_id, C.c_id
	FROM Country C
	INNER JOIN Resident R ON R.r_id = C.c_id
	INNER JOIN Town T ON T.t_id = C.c_id
	WHERE T.town_quality_factor > 20 AND R.r_adress < 150

GO

-- Cost with existing indexes(the automatically created ones + nonclustered index on Town): 0.262022
-- When adding a nonclustered index on r_adress to the existing indexes: 0.251297
-- Without the nonclustered index on Town and the nonclustered index on Resident: 0.308787
-- Automatically created indexes + nonclustered index on town_quality_factor + nonclustered index on r_adress + nonclustered index on (r_id, t_id) from Country: 0.249815
select *from Join1

create nonclustered index Resident_adress_index ON Resident(r_adress)
DROP INDEX Resident_adress_index ON Resident

create nonclustered index Country_ids_index ON Country(r_id,t_id)
drop index Country_ids_index ON Country 