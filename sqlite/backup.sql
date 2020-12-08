BEGIN TRANSACTION;
CREATE TABLE SensorData(one varchar(10), two smallint);
INSERT INTO "SensorData" VALUES('hello!',10);
INSERT INTO "SensorData" VALUES('goodbye',20);
COMMIT;
