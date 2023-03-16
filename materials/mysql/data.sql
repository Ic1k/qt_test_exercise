CREATE DATABASE device;

USE device;

CREATE TABLE devices(
  deviceId INT NOT NULL AUTO_INCREMENT,
  name VARCHAR(100) NOT NULL,
  PRIMARY KEY (deviceId)
);

INSERT INTO devices(
  name
) VALUES(
  "BMK - 4"
),
(
  "BMK - 6"
),
(
  "MT - 5"
),
(
  "MT - 21"
),
(
  "MT - 22"
),
(
  "MT - 23"
),
(
  "MT - 24"
);
