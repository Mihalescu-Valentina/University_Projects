USE Eurovision;

--a modify the type of a column
GO
CREATE OR ALTER PROCEDURE setMoneyPaidFromIntToDecimal 
AS
    ALTER TABLE Sponsors ALTER COLUMN money_paid DECIMAL(10,2)

GO
CREATE OR ALTER PROCEDURE setMoneyPaidFromDecimalToInt
AS
	ALTER TABLE Sponsors ALTER COLUMN money_paid INT


--b add / remove a column
GO
CREATE OR ALTER PROCEDURE addArtistAge
AS
    ALTER TABLE Artist ADD age INT

GO
CREATE OR ALTER PROCEDURE removeArtistAge
AS
    ALTER TABLE Artist DROP COLUMN age



--c add / remove a DEFAULT constraint;
GO
CREATE OR ALTER PROCEDURE addDefaultJobConstraint
AS
	ALTER TABLE Host
		ADD CONSTRAINT df_Job
		DEFAULT 'Presenter' FOR Job;


GO
CREATE OR ALTER PROCEDURE removeDefaultJobConstraint
AS
	ALTER TABLE Host DROP CONSTRAINT df_Job



--d add / remove a primary key
GO 
CREATE OR ALTER PROCEDURE addHostPrimaryKey
AS
	ALTER TABLE Host 
		DROP CONSTRAINT PK_Host
	ALTER TABLE Host
		ADD CONSTRAINT PK_Host PRIMARY KEY(h_id,screentime)

GO 
CREATE OR ALTER PROCEDURE removeHostPrimaryKey
AS
	ALTER TABLE Host
		DROP CONSTRAINT PK_Host
	ALTER TABLE Host
		ADD CONSTRAINT PK_Host PRIMARY KEY(h_id)


--e add / remove a candidate key;
GO
CREATE OR ALTER PROCEDURE newCandidateKeyHostName
AS	
	ALTER TABLE Host
		ADD CONSTRAINT CK_HostName UNIQUE(h_id, h_name)

GO
CREATE OR ALTER PROCEDURE removeCandidateKeyHostName
AS
	ALTER TABLE Host
		DROP CONSTRAINT CK_HostName 


--f add / remove a foreign key;
GO
CREATE OR ALTER PROCEDURE addForeignKeyHostEditionId
AS
	ALTER TABLE Host
		ADD CONSTRAINT FK_HostEditionId FOREIGN KEY(edition_id) REFERENCES Edition(edition_id)

GO
CREATE OR ALTER PROCEDURE removeForeignKeyHostEditionId
AS
	ALTER TABLE Host
		DROP CONSTRAINT FK_HostEditionId 


--g create / drop a table.
GO
CREATE OR ALTER PROCEDURE addHostId
AS
	CREATE TABLE HostId (
	h_id INT FOREIGN KEY REFERENCES Host(h_id),
	edition_id INT FOREIGN KEY REFERENCES Edition(edition_id),
	UNIQUE(h_id,edition_id)
		
	)

GO 
CREATE OR ALTER PROCEDURE dropHostId
AS
	DROP TABLE HostId


-- a table that contains the current version of the database schema

CREATE TABLE crtVersionTable (
	crtVersion INT
)

INSERT INTO crtVersionTable 
VALUES
	(1)  -- this is the initial version


CREATE TABLE databaseVersion (
	initial_version INT,
	final_version INT,
	prcd_name VARCHAR(100),
	PRIMARY KEY (initial_version, final_version)

)

INSERT INTO databaseVersion
VALUES
	(1, 2, 'setMoneyPaidFromIntToDecimal '),
	(2, 1, 'setMoneyPaidFromDecimalToInt'),
	(2, 3, 'addArtistAge'), 
	(3, 2, 'removeArtistAge'),
	(3, 4, 'addDefaultJobConstraint'),
	(4, 3, 'removeDefaultJobConstraint'),
	(4, 5, 'addHostPrimaryKey'),
	(5, 4, 'removeHostPrimaryKey'),
	(5, 6, 'newCandidateKeyHostName'),
	(6, 5, 'removeCandidateKeyHostName'),
	(6, 7, 'addForeignKeyHostEditionId'),
	(7, 6, 'removeForeignKeyHostEditionId'),
	(7, 8, 'addHostId'),
	(8, 7, 'dropHostId')

GO
CREATE OR ALTER PROCEDURE goToVersion(@newVersion INT) 
AS
	DECLARE @currentVersion INT
	DECLARE @procedureName VARCHAR(MAX)
	SELECT @currentVersion = crtVersion FROM crtVersionTable
	
	IF (@newVersion > (SELECT MAX(final_version) FROM dataBaseVersion) OR @newVersion < 1)
		RAISERROR ('Bad version', 10, 1) --10 is the severity, 1 the state of the error

	
	ELSE 
	BEGIN
		IF @newVersion = @currentVersion
			PRINT('You are already on this version! Introduce another version index!');
		ELSE
		BEGIN
			IF @currentVersion > @newVersion
			BEGIN
				WHILE @currentVersion > @newVersion 
					BEGIN
						SELECT @procedureName = prcd_name FROM databaseVersion WHERE initial_version = @currentVersion AND final_version = @currentVersion-1
						PRINT('The procedure that is executing is ' + @procedureName);
						EXEC (@procedureName)
						SET @currentVersion = @currentVersion - 1
					END
			END

			IF @currentVersion < @newVersion
			BEGIN
				WHILE @currentVersion < @newVersion 
					BEGIN
						SELECT @procedureName = prcd_name FROM databaseVersion WHERE initial_version = @currentVersion AND final_version = @currentVersion+1
						PRINT('The procedure that is executing is ' + @procedureName);
						EXEC (@procedureName)
						SET @currentVersion = @currentVersion + 1
					END
			END

			UPDATE crtVersionTable SET crtVersion = @newVersion
		END
	END

EXEC goToVersion 1

SELECT *
FROM crtVersionTable

SELECT *
FROM databaseVersion
	
	










