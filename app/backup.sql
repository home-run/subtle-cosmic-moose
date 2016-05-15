PRAGMA foreign_keys=ON;
BEGIN TRANSACTION;
CREATE TABLE stadiums(
	id INTEGER PRIMARY KEY AUTOINCREMENT,
	name text not null unique,
	team text not null unique,
	address text not null unique,
	phone text not null unique,
	date text not null,
	capacity text not null,
	turf text not null, 
	revenue real default 0.0,
	league text not null,
        typology text not null
	);
INSERT INTO "stadiums" VALUES(1,'Angels Stadium of Anaheim','Los Angeles Angels of Anaheim','2000 E Gene Autry Way Anaheim, CA 92806','(714) 940-2000','1966-04-19','45,957','Grass','0','American','Retro Modern');
INSERT INTO "stadiums" VALUES(2,'Comerica Park','Detroit Tigers','2100 Woodward Ave Detroit MI, 48201','(313) 962-4000','2000-04-11','41,547','Grass','0','American','Retro Classic');
INSERT INTO "stadiums" VALUES(3,'Fenway Park','Boston Red Sox','4 Yawkey Way Boston MA, 02215','(877) 733-7699','1912-04-20','37,673','Grass','0','American','Jewel Box');
INSERT INTO "stadiums" VALUES(4,'Globe Life Park in Arlington','Texas Rangers','1000 Ballpark Way Arlington TX, 76011','(817) 273-5222','1994-04-01','48,114','Grass','0','American','Retro Classic');
INSERT INTO "stadiums" VALUES(5,'Kauffman Stadium','Kansas City Royals','1 Royal Way Kansas City MO, 64129','(816) 921-8000','1973-04-10','37,903','Grass','0','American','Retro Modern');
INSERT INTO "stadiums" VALUES(6,'Minute Maid Park','Houston Astros','501 Crawford St Houston TX, 77002','(713) 259-8000','2000-03-30','421,574','Grass','0','American','Retro Modern');
INSERT INTO "stadiums" VALUES(7,'O.co Coliseum','Oakland Athletics','7000 Coliseum Way Oakland CA, 94621','(510) 569-2121','1966-09-18','35,067','Grass','0','American','Multipurpose');
INSERT INTO "stadiums" VALUES(8,'Oriole Park at Camden Yards','Baltimore Orioles','333 West Camden Street Baltimore MD, 21201','(410) 685-9800','1992-04-06','45,971','Grass','0','American','Retro Classic');
INSERT INTO "stadiums" VALUES(9,'Progressive Field','Cleveland Indians','2401 Ontario Street Cleveland OH, 44115','(216) 420-4487','1994-04-02','37,675','Grass','0','American','Retro Modern');
INSERT INTO "stadiums" VALUES(10,'Rogers Centre','Totonto Blue Jays','1 Blue Jays Way Toronto Ontario, Canada M5V1J3','+1 (416) 314-1000','1989-06-03','49,282','Astro Turf','0','American','Multipurpose');
INSERT INTO "stadiums" VALUES(11,'SafeCo Field','Seattle Mariners','1516 First Avenue South Seattle WA, 98134','(206) 346-4000','1999-07-15','47,574','Grass','0','American','Retro Modern');
INSERT INTO "stadiums" VALUES(12,'Target Field','Minnesota Twins','353 N 5th St Minneapolis MN, 55403','(800) 338-9467','2010-04-12','39,021','Grass','0','American','Retro Modern');
INSERT INTO "stadiums" VALUES(13,'Tropicana Field','Tampa Bay Rays','1 Tropicana Dr St. Petersburg FL, 33705','(727) 825-3137','1990-03-03','31,042','Astro Turf','0','American','Multipurpose');
INSERT INTO "stadiums" VALUES(14,'US Cellular Field','Chicago White Sox','333 West 35th Street Chicago IL, 60616','(312) 674-1000','1991-04-18','40,615','Grass','0','American','Retro Classic');
INSERT INTO "stadiums" VALUES(15,'Yankee Stadium','New York Yankees','1 E 161st St South Bronx NY, 10451','(718) 293-4300','2009-04-16','49,642','Grass','0','American','Retro Classic');
INSERT INTO "stadiums" VALUES(16,'AT&T Park','San Francisco Giants','24 Willie Mays Plaza San Francisco CA, 94107','(415) 972-2000','2000-04-11','41,915','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(17,'Busch Stadium','St. Louis Cardinals','700 Clark Street St. Louis MO, 63102','(314) 345-9600','2006-04-10','43,975','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(18,'Chase Field','Arizona Diamondbacks','401 East Jefferson Street Phoenix AZ, 85004','(602) 462-6500','1998-03-31','48,519','Grass','0','National','Retro Modern');
INSERT INTO "stadiums" VALUES(19,'Citi Field','New York Mets','126th St & Roosevelt Ave','(718) 507-6387','2009-04-13','41,922','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(20,'Citizens Bank Park','Philadelphia Phillies','1 Citizens Bank Way Philadelphia PA, 19148','(215) 463-1000','2004-04-03','43,651','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(21,'Coors Field','Colorado Rockies','2001 Blake St Denver CO, 80205','(303) 292-0200','1995-04-26','50,398','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(22,'Dodger Stadium','Los Angeles Dodgers','1000 Elysian Park Avenue Los Angeles CA, 90090','(323) 224-1507','1962-04-10','56,000','Grass','0','National','Modern');
INSERT INTO "stadiums" VALUES(23,'Great America Ball Park','Cincinnati Reds','100 Joe Nuxhall Way Cincinnati OH, 45202','(513) 381-7337','2003-03-31','42,319','Grass','0','National','Retro Modern');
INSERT INTO "stadiums" VALUES(24,'Marlins Park','Miami Marlins','501 Marlins Way Miami FL, 33125','(305) 480-1300','2012-04-04','36,742','Grass','0','National','Contemporary');
INSERT INTO "stadiums" VALUES(25,'Miller Park','Milwaukee Brewers','1 Brewers Way Milwaukee WI, 53214','(414) 902-4400','2001-04-06','41,900','Grass','0','National','Retro Modern');
INSERT INTO "stadiums" VALUES(26,'Nationals Park','Washington Nationals','1500 S Capitol St SE Washington, DC, 20003','(202) 675-6287','2008-03-30','41,888','Grass','0','National','Retro Modern');
INSERT INTO "stadiums" VALUES(27,'Petco Park','San Diego Padres','19 Tony Gwynn Drive San Diego CA, 92101','(619) 795-5000','2004-04-08','41,164','Grass','0','National','Retro Modern');
INSERT INTO "stadiums" VALUES(28,'PNC Park','Pittsburgh Pirates','115 Federal St Pittsburgh PA, 15212','(412) 321-2827','2001-03-31','38,362','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(29,'Turner Field','Atlanta Braves','755 Hank Aaron Drive Atlanta GA, 30315','(404) 522-7630','1997-03-29','49,586','Grass','0','National','Retro Classic');
INSERT INTO "stadiums" VALUES(30,'Wrigley Field','Chicago Cubs','1060 West Addison Street Chicago IL, 60613','(773) 404-2827','1914-04-23','42,495','Grass','0','National','Jewel Box');
CREATE TABLE souvenirs(
    stadium_id int references stadiums(id) ON DELETE CASCADE,
    name text not null,
    price text not null);
INSERT INTO "souvenirs" VALUES(1,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(1,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(1,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(1,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(1,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(2,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(2,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(2,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(2,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(2,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(3,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(3,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(3,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(3,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(3,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(4,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(4,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(4,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(4,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(4,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(5,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(5,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(5,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(5,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(5,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(6,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(6,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(6,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(6,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(6,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(7,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(7,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(7,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(7,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(7,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(8,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(8,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(8,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(8,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(8,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(9,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(9,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(9,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(9,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(9,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(10,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(10,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(10,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(10,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(10,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(11,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(11,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(11,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(11,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(11,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(12,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(12,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(12,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(12,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(12,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(13,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(13,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(13,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(13,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(13,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(14,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(14,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(14,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(14,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(14,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(15,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(15,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(15,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(15,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(15,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(16,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(16,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(16,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(16,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(16,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(17,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(17,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(17,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(17,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(17,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(18,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(18,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(18,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(18,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(18,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(19,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(19,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(19,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(19,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(19,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(20,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(20,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(20,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(20,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(20,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(21,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(21,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(21,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(21,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(21,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(22,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(22,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(22,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(22,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(22,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(23,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(23,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(23,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(23,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(23,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(24,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(24,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(24,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(24,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(24,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(25,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(25,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(25,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(25,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(25,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(26,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(26,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(26,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(26,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(26,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(27,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(27,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(27,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(27,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(27,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(28,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(28,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(28,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(28,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(28,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(29,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(29,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(29,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(29,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(29,'Team jersey','85.99');
INSERT INTO "souvenirs" VALUES(30,'Baseball cap','23.99');
INSERT INTO "souvenirs" VALUES(30,'Baseball bat','45.39');
INSERT INTO "souvenirs" VALUES(30,'Team pendant','15.99');
INSERT INTO "souvenirs" VALUES(30,'Autographed baseball','19.99');
INSERT INTO "souvenirs" VALUES(30,'Team jersey','85.99');
CREATE TABLE distances(
        id_from int references stadiums(id) ON DELETE CASCADE,
        id_to int references stadiums(id) ON DELETE CASCADE,
        distance int);
INSERT INTO "distances" VALUES(1,27,110);
INSERT INTO "distances" VALUES(1,22,50);
INSERT INTO "distances" VALUES(2,10,210);
INSERT INTO "distances" VALUES(2,9,90);
INSERT INTO "distances" VALUES(2,14,240);
INSERT INTO "distances" VALUES(3,10,430);
INSERT INTO "distances" VALUES(3,19,195);
INSERT INTO "distances" VALUES(3,24,1255);
INSERT INTO "distances" VALUES(4,21,650);
INSERT INTO "distances" VALUES(4,18,870);
INSERT INTO "distances" VALUES(4,29,740);
INSERT INTO "distances" VALUES(4,6,230);
INSERT INTO "distances" VALUES(4,5,460);
INSERT INTO "distances" VALUES(5,21,560);
INSERT INTO "distances" VALUES(5,30,415);
INSERT INTO "distances" VALUES(5,17,235);
INSERT INTO "distances" VALUES(5,4,460);
INSERT INTO "distances" VALUES(6,18,1115);
INSERT INTO "distances" VALUES(6,13,790);
INSERT INTO "distances" VALUES(6,24,965);
INSERT INTO "distances" VALUES(6,4,230);
INSERT INTO "distances" VALUES(7,16,50);
INSERT INTO "distances" VALUES(7,18,650);
INSERT INTO "distances" VALUES(7,22,340);
INSERT INTO "distances" VALUES(8,26,50);
INSERT INTO "distances" VALUES(8,20,90);
INSERT INTO "distances" VALUES(9,2,90);
INSERT INTO "distances" VALUES(9,23,225);
INSERT INTO "distances" VALUES(9,28,115);
INSERT INTO "distances" VALUES(10,3,430);
INSERT INTO "distances" VALUES(10,11,2070);
INSERT INTO "distances" VALUES(10,25,430);
INSERT INTO "distances" VALUES(10,2,210);
INSERT INTO "distances" VALUES(10,28,225);
INSERT INTO "distances" VALUES(11,16,680);
INSERT INTO "distances" VALUES(11,10,2070);
INSERT INTO "distances" VALUES(11,12,1390);
INSERT INTO "distances" VALUES(12,11,1390);
INSERT INTO "distances" VALUES(12,22,1500);
INSERT INTO "distances" VALUES(12,17,465);
INSERT INTO "distances" VALUES(12,25,300);
INSERT INTO "distances" VALUES(13,23,790);
INSERT INTO "distances" VALUES(13,6,790);
INSERT INTO "distances" VALUES(13,24,210);
INSERT INTO "distances" VALUES(14,30,50);
INSERT INTO "distances" VALUES(14,2,240);
INSERT INTO "distances" VALUES(14,23,250);
INSERT INTO "distances" VALUES(15,19,50);
INSERT INTO "distances" VALUES(15,20,80);
INSERT INTO "distances" VALUES(15,28,315);
INSERT INTO "distances" VALUES(16,11,680);
INSERT INTO "distances" VALUES(16,7,50);
INSERT INTO "distances" VALUES(17,6,680);
INSERT INTO "distances" VALUES(17,5,235);
INSERT INTO "distances" VALUES(17,23,310);
INSERT INTO "distances" VALUES(17,12,465);
INSERT INTO "distances" VALUES(18,7,650);
INSERT INTO "distances" VALUES(18,27,300);
INSERT INTO "distances" VALUES(18,21,580);
INSERT INTO "distances" VALUES(18,4,870);
INSERT INTO "distances" VALUES(18,6,1115);
INSERT INTO "distances" VALUES(19,15,50);
INSERT INTO "distances" VALUES(19,3,195);
INSERT INTO "distances" VALUES(20,15,80);
INSERT INTO "distances" VALUES(20,8,90);
INSERT INTO "distances" VALUES(21,5,560);
INSERT INTO "distances" VALUES(21,4,650);
INSERT INTO "distances" VALUES(21,18,580);
INSERT INTO "distances" VALUES(21,27,830);
INSERT INTO "distances" VALUES(22,1,50);
INSERT INTO "distances" VALUES(22,7,340);
INSERT INTO "distances" VALUES(22,12,1500);
INSERT INTO "distances" VALUES(23,17,310);
INSERT INTO "distances" VALUES(23,29,375);
INSERT INTO "distances" VALUES(23,13,790);
INSERT INTO "distances" VALUES(23,28,260);
INSERT INTO "distances" VALUES(23,9,225);
INSERT INTO "distances" VALUES(23,14,250);
INSERT INTO "distances" VALUES(24,13,210);
INSERT INTO "distances" VALUES(24,6,965);
INSERT INTO "distances" VALUES(24,3,1255);
INSERT INTO "distances" VALUES(24,26,930);
INSERT INTO "distances" VALUES(24,29,600);
INSERT INTO "distances" VALUES(25,12,300);
INSERT INTO "distances" VALUES(25,30,80);
INSERT INTO "distances" VALUES(25,10,430);
INSERT INTO "distances" VALUES(26,8,50);
INSERT INTO "distances" VALUES(26,28,195);
INSERT INTO "distances" VALUES(26,29,560);
INSERT INTO "distances" VALUES(26,24,930);
INSERT INTO "distances" VALUES(27,1,110);
INSERT INTO "distances" VALUES(27,18,300);
INSERT INTO "distances" VALUES(27,21,830);
INSERT INTO "distances" VALUES(28,9,115);
INSERT INTO "distances" VALUES(28,23,260);
INSERT INTO "distances" VALUES(28,26,195);
INSERT INTO "distances" VALUES(28,15,315);
INSERT INTO "distances" VALUES(28,10,225);
INSERT INTO "distances" VALUES(29,4,740);
INSERT INTO "distances" VALUES(29,24,600);
INSERT INTO "distances" VALUES(29,26,560);
INSERT INTO "distances" VALUES(29,23,375);
INSERT INTO "distances" VALUES(30,14,50);
INSERT INTO "distances" VALUES(30,25,80);
INSERT INTO "distances" VALUES(30,5,415);
INSERT INTO "distances" VALUES(6,17,680);
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('stadiums',30);
COMMIT;