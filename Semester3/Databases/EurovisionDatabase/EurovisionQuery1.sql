CREATE TABLE Country(
	country_id INT PRIMARY KEY,
	country_name VARCHAR(150) UNIQUE,
	year_of_entrance INT,
	country_capital VARCHAR(100) UNIQUE,
	quality_factor INT,
);

CREATE TABLE HostCity(
	host_city_id INT PRIMARY KEY,
	host_city_name VARCHAR(100) UNIQUE,
	host_city_population INT,
	quality_factor INT,
);


CREATE TABLE Venue(
	venue_id INT PRIMARY KEY,
	venue_name VARCHAR(200),
	host_city_id INT FOREIGN KEY REFERENCES HostCity(host_city_id),
	capacity INT,

);

CREATE TABLE Edition(
	edition_id INT PRIMARY KEY,
	edition_year INT UNIQUE,
	final_date DATE,
	motto VARCHAR(100),
	venue_id INT FOREIGN KEY REFERENCES Venue(venue_id),
	winner_id INT FOREIGN KEY REFERENCES Country(country_id),

);

CREATE TABLE Artist(
	artist_id INT PRIMARY KEY,
	artist_name VARCHAR(200),
	artist_type VARCHAR(100),
);

CREATE TABLE Song(
	song_id INT PRIMARY KEY,
	song_name VARCHAR(100),
	artist_id INT FOREIGN KEY REFERENCES Artist(artist_id),

);


CREATE TABLE Ids(
	edition_id INT FOREIGN KEY REFERENCES Edition(edition_id),
	country_id INT FOREIGN KEY REFERENCES Country(country_id),
	song_id INT FOREIGN KEY REFERENCES Song(song_id),
	UNIQUE(edition_id,country_id,song_id),
);


CREATE TABLE Sponsors(
	sponsor_id INT PRIMARY KEY,
	sponsor_name VARCHAR(100),
	money_paid INT,
	edition_id INT FOREIGN KEY REFERENCES Edition(edition_id)
);


CREATE TABLE SpokePerson(
	sp_id INT PRIMARY KEY,
	sp_name VARCHAR(100),
	job VARCHAR(100),
	place_of_report VARCHAR(100),
	previous_contestant VARCHAR(10),

);

CREATE TABLE SpokePersonId(
	sp_id INT FOREIGN KEY REFERENCES SpokePerson(sp_id),
	edition_id INT FOREIGN KEY REFERENCES Edition(edition_id),
	country_id INT FOREIGN KEY REFERENCES Country(country_id),
	UNIQUE(sp_id,edition_id,country_id),


);




