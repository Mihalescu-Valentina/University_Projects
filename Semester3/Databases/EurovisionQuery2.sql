INSERT INTO Country(country_id,country_name,year_of_entrance,country_capital,quality_factor) VALUES (3,'Latvia',2000,'Riga',29340),(2,'UK',1956,'London',10000),(1,'Belarus',2004,'Minsk',10000),(10,'Israel',1973,'Jerusalem',10000),
(11,'Germany',1956,'Berlin',10000),(12,'Sweeden',1958,'StockHolm',10000),(13,'Romania',1994,'Bucharest',10000),
(14,'Poland',1994,'Warsaw',10000),(15,'Italy',1956,'Rome',10000),(16,'Greece',1974,'Athens',10000),(17,'Azerbaidjan',2008,'Baku',10000),(18,'Ukraine',2003,'Kiev',10000),(19,'Finland',1961,'Helsinki',10000);
INSERT INTO HostCity(host_city_id,host_city_name,host_city_population,quality_factor) VALUES (28,'Rome',2761000,20),(27,'Malmo',361000,20),(26,'Kiev',2000000,20),(20,'Athens',3000000,20),(21,'Istanbul',15000000,20),
(22,'Dusseldorf',620000,20),(23,'Baku',2000000,20),(24,'Riga',605000,20),(25,'Turin',886000,20);
INSERT INTO Venue(venue_id,venue_name,host_city_id,capacity) VALUES (36,'Expo Rome',28,12270),(35,'The Pala Olimpico',25,19200),(30,'Olympic Indoor Hall Athens',20,19200),
(31,'Abdi İpekçi Arena',21,12270),(32,'Düsseldorf Arena',22,54600),(33,'Baku Crystal Hall',23,12000),(34,'Skonto Hall',24,8000);
INSERT INTO Edition(edition_id,edition_year,final_date,motto,venue_id,winner_id) VALUES (47,1982,'1982-05-28','',32,11),(46,2020,'','Open up',33,NULL),(45,2015,'2015-05-30','',32,NULL),(44,2010,'2010-05-29','',33,11),(40,2006,'2006-05-20','',30,19),(41,2004,'2004-05-14','',31,18),
(42,2011,'2011-05-14','Feel your heart beat',32,17),(103,2012,'2012-05-26','Light your fire',33,12);
INSERT INTO Artist(artist_id,artist_name,artist_type) VALUES (59,'Paula Seling & Ovi','duo'),(58,'Lena','solo'),(57,'Helena Paparizou','solo'),(50,'Rosa Linn',NULL),(51,'Lordi','band'),(52,'WRS','solo'),
(53,'Ruslana','solo'),(54,'Eleni Foureira','solo'),(55,'Ell & Nikki','duo'),(56,'Loreen','solo');
INSERT INTO Sponsors(sponsor_id,sponsor_name,money_paid,edition_id) VALUES (67,'Facebook',10000,46),(66,'Paypal',600000,43),(65,'Youtube',3500000,47),(64,'Tesla',500000,43),(60,'Moroccanoil',500000,42),(61,'My Heritage',700000,40),(62,'Vine',1000000,41),(63,'Instagram',200000,49) ;--63 instagram 2000000 49 does not satisfy the integrity constarint
INSERT INTO Song(song_id,song_name,artist_id) VALUES (77,'Playing with fire',59),(76,'Taken by a stranger',58),(75,'My number one',57),(74,'Running out scared',55),(70,'Euphoria',56),(71,'Snap',50),(72,'Hard Rock Haleluiah',51),(73,'Hola mi bebe',52);
INSERT INTO SpokePerson(sp_id,sp_name,job,place_of_report,previous_contestant) VALUES (84,'Loreen','singer','Serek National Park','yes'),
(85,'Andrew Garfield','actor','UK Park','No'),(80,'TIX','singer','Geiranger Fiord','yes'),(81,'Catalina Ponor','gymnast','Arcul de Triumf','No'),(82,'Otto','singer','Georgi town hall','yes'),(83,'Stefania','singer','Mikonos','yes');
INSERT INTO Ids(edition_id,country_id,song_id) VALUES (43,13,77),(42,11,76),(43,12,70),(40,16,75),(42,11,74);
INSERT INTO SpokePersonId(sp_id,edition_id,country_id) VALUES (84,43,12),(80,42,17),(81,41,13),(85,40,12)
INSERT INTO Host(h_id,edition_id,screentime,h_name,job,previous_contestant) VALUES (90,44,200,'Nikkie','vlogger','yes');
ALTER TABLE Host alter column h_id int NOT NULL
ALTER TABLE Host alter column h_name VARCHAR(100) 
ALTER TABLE Host ADD CONSTRAINT PK_Host PRIMARY KEY (h_id)
UPDATE HostCity SET host_city_population = host_city_population+10 WHERE host_city_name LIKE 'R%';
UPDATE Sponsors SET money_paid = money_paid/10 WHERE sponsor_name = 'MyHeritage' OR edition_id = 41 ; --money paid is now 100000
UPDATE Artist SET artist_type = 'solo' WHERE artist_type IS NULL;
UPDATE Edition SET edition_id = 43 WHERE edition_id > 100;
UPDATE HostCity SET quality_factor= host_city_population/1000+20;
UPDATE Country SET quality_factor  = year_of_entrance+10;
DELETE FROM Country WHERE country_id NOT in (10,11,12,13,14,15,16,17,18,19);
DELETE FROM Venue WHERE capacity BETWEEN 1000 AND 10000 ;

--a
--finds the id of the artists that are solo or that have their name starting with an 'H' 
SELECT  S.artist_id AS 'id of the artists that are solo or whose song s name starts with an H'
FROM Artist A,Song S
WHERE A.artist_id = S.artist_id and artist_type = 'solo'
UNION
SELECT S1.artist_id AS 'id of the artists that are solo or whose song s name starts with an H'
FROM Artist A1,Song S1
WHERE S1.artist_id = S1.artist_id AND S1.song_name LIKE 'H%';

--finds the editions that don't have a motto or took place after year 2010(ordered descending)
SELECT E.edition_id,E.motto,E.edition_year
FROM Edition E
WHERE E.motto!='' OR E.edition_year >=2010
ORDER BY E.edition_year DESC


--b
--host cities that are also a capital and entered the contest after 2000(order ascending)
SELECT DISTINCT H.host_city_name,H.quality_factor+10 AS NQF 
FROM HostCity H,Country C
WHERE H.host_city_name IN 
(SELECT  DISTINCT C1.country_capital 
FROM Country C1
WHERE C1.year_of_entrance >2000)
ORDER BY H.host_city_name ASC;


--find the ids of the venues that have a capacity between 11000 and 20000 seats and are placed in a host city with a population between 2 million and 3 million people
SELECT H.host_city_id,V.venue_id
FROM HostCity H, Venue V
WHERE H.host_city_id = V.host_city_id AND V.capacity BETWEEN 11000 AND 20000
INTERSECT
SELECT H2.host_city_id,V2.venue_id
FROM HostCity H2,Venue V2
WHERE H2.host_city_id = V2.host_city_id AND H2.host_city_population BETWEEN 2000000 AND 3000000;

--c
--finds the countries that have a capital which didn't host the contest
SELECT C.country_id,C.country_capital
FROM Country C
WHERE C.country_capital NOT IN
(SELECT H.host_city_name
FROM HostCity H
);

--finds the name of all the spokepersons that have not been previous contestants
SELECT S.sp_name AS 'spoke persons that have not been previous contestants'
FROM SpokePerson S
EXCEPT 
SELECT S1.sp_name
FROM SpokePerson S1
WHERE S1.previous_contestant='Yes';

--d
--joins 3 many to many relations(Edition,Ids,Song)
SELECT edition_year,country_name,song_name
FROM  Ids
INNER JOIN Edition
ON Edition.edition_id = Ids.edition_id
INNER JOIN Country
ON Ids.country_id = Country.country_id
INNER JOIN Song
ON Ids.song_id = Song.song_id;

/*SELECT DISTINCT sp_name,edition_year,country_name
FROM SpokePersonId
LEFT JOIN SpokePerson
ON SpokePerson.sp_id = SpokePersonId.sp_id
LEFT JOIN Edition
ON SpokePersonId.edition_id = Edition.edition_id
LEFT JOIN Country
ON Country.country_id = SpokePersonId.country_id;*/


--display the details about all the sponsors as well as the sponsored editions;include editions that are not sponsored
SELECT *
FROM EDITION
LEFT JOIN Sponsors
ON Sponsors.edition_id = Edition.edition_id;

--display the information about all the venues(include the names of the host cities);include also host cities without venues added yet
SELECT*
FROM VENUE
RIGHT JOIN HostCity
ON HostCity.host_city_id = Venue.host_city_id;

--display the editions as well as the country information for all the winning countries(include countries that NEVER won and editions WITHOUT winners)
SELECT*
FROM Edition
FULL JOIN Country
ON Edition.winner_id = Country.country_id;

--e
--finds the editions in which took part at least one duet
SELECT *
FROM Edition
WHERE edition_id IN (
	SELECT edition_id
	FROM Ids
	WHERE song_id IN(
	SELECT song_id
	FROM Song
	WHERE artist_id IN(
	SELECT artist_id
	FROM Artist
	WHERE artist_type = 'duo')))

--finds the venues that are located in a host city with a quality factor over 1000
SELECT TOP 2 venue_id,venue_name,host_city_id,capacity
FROM Venue
WHERE host_city_id IN(
	SELECT host_city_id
	FROM HostCity H
	WHERE H.quality_factor >1000
)
--select*
--from HostCity H                                                       this code is used for checking the corectitude of the previous one
--where H.host_city_id in (select host_city_id from Venue)

--f
--display the names of the countries that have a winner and have entered the competition after the year 2000
SELECT country_name
FROM Country
WHERE EXISTS (SELECT edition_id FROM Edition WHERE Edition.winner_id = Country.country_id AND Country.year_of_entrance < 2000);

--finds the editions that took place in a venue with a capacity close to 20000 seats
SELECT edition_id,edition_year,venue_id
FROM Edition E
WHERE EXISTS (SELECT venue_id FROM Venue V WHERE V.venue_id = E.venue_id AND (V.capacity+1000)>20000 )




--g
--finds the top 2 sponsors of the 2000's editions in terms of the money paid
SELECT TOP 2 A.money_paid
FROM (SELECT money_paid
FROM Sponsors S
WHERE S.edition_id IN(
SELECT edition_id FROM Edition E WHERE E.edition_year<2010
)
) AS A

--finds the spokepersons that offered the points from a winning country
SELECT B.sp_id
FROM (SELECT sp_id
FROM SpokePersonId S
WHERE S.country_id IN (
SELECT winner_id
FROM Edition E
)
)AS B

--h
--finds venues that have a capacity lower than the highest one; grouped by the capacity

SELECT COUNT(capacity) ,capacity
FROM Venue V
GROUP BY capacity
HAVING V.capacity<(SELECT MAX(capacity) FROM Venue);

--finds host cities that have the quality factor less than the average one
SELECT COUNT(quality_factor), quality_factor
FROM HostCity H
GROUP BY quality_factor
HAVING H.quality_factor<(SELECT AVG(quality_factor) FROM HostCity);

--finds the sponsors that paid less than the total sum paid by the sponsors in the editions that had a motto
SELECT COUNT(money_paid),money_paid
FROM Sponsors S
GROUP BY money_paid
HAVING S.money_paid<(SELECT SUM(money_paid) FROM Sponsors S WHERE S.edition_id IN (SELECT E.edition_id FROM Edition E WHERE E.motto != ''))

--groups countries by the year of entrance and orders the result descending by the year of entry
SELECT COUNT(year_of_entrance), year_of_entrance
FROM Country C
GROUP BY year_of_entrance
ORDER BY year_of_entrance DESC

--i
--finds the songs that are sang by a solo artist
SELECT song_name
FROM Song S
WHERE S.song_id = ANY(
SELECT  song_id FROM Ids I WHERE I.song_id = S.song_id  AND S.artist_id IN (SELECT artist_id FROM Artist A where A.artist_type = 'solo')
)

SELECT song_name
FROM Song S
WHERE S.song_id IN (SELECT  song_id FROM Ids I WHERE I.song_id = S.song_id  AND S.artist_id IN (SELECT artist_id FROM Artist A where A.artist_type = 'solo')
)

--finds the cities that have their quality factor larger than the minimum quality factor of the countries
SELECT host_city_name,quality_factor
FROM HostCity H
WHERE H.quality_factor > (SELECT MIN(quality_factor) FROM Country c)

SELECT host_city_name,quality_factor
FROM HostCity H
WHERE H.quality_factor > ANY(SELECT quality_factor FROM Country c)

--finds the editions that have a greater budget than the maximum amount of money paid by a sponsor in the history of the contest
SELECT edition_id,edition_year,budget
FROM Edition E
Where E.budget >(SELECT MAX(money_paid) FROM Sponsors)

SELECT edition_id,edition_year,budget
FROM Edition E
Where E.budget >ALL(SELECT (money_paid) FROM Sponsors)

--filters the cities that are not capitals
SELECT host_city_name
FROM HostCity H
WHERE H.host_city_name NOT IN (SELECT country_capital FROM Country C )

SELECT host_city_name
FROM HostCity H
WHERE H.host_city_name != ALL(SELECT country_capital FROM Country C )

















