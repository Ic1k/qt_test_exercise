CREATE DATABASE vega_db;

USE vega_db;


CREATE TABLE devices
(
    id   INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255)
);

CREATE TABLE processes
(
    id   INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255)
);

CREATE TABLE files
(
    id   INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255)
);


CREATE TABLE data
(
    id         INT PRIMARY KEY AUTO_INCREMENT,
    device_id  INT,
    process_id INT,
    file_id    INT,
    FOREIGN KEY (device_id) REFERENCES devices (id),
    FOREIGN KEY (process_id) REFERENCES processes (id),
    FOREIGN KEY (file_id) REFERENCES files (id)
);



INSERT INTO devices(name)
VALUES ("BMK - 4"),
       ("BMK - 6"),
       ("MT - 23"),
       ("MT - 24");

INSERT INTO processes(name)
VALUES ("soldering"),
       ("testing"),
       ("packaging");

INSERT INTO files(name)
VALUES ("firmware_vmk4.bin"),
       ("firmware_vmk6.bin"),
       ("firmware_mt23.bin"),
       ("firmware_mt24.bin"),
       ("1A5-CITC.pdf"),
       ("instr_ot_001doc.pdf"),
       ("N26-OH.pdf");

INSERT INTO data(device_id, process_id, file_id)
VALUES (1, 1, 5),
       (1, 1, 6),
       (1, 2, 1),
       (1, 2, 6),
       (1, 3, 6),
       (1, 3, 7),
       (2, 1, 5),
       (2, 1, 6),
       (2, 2, 2),
       (2, 2, 6),
       (2, 3, 6),
       (2, 3, 7),
       (3, 1, 5),
       (3, 1, 6),
       (3, 2, 3),
       (3, 2, 6),
       (3, 3, 6),
       (3, 3, 7),
       (4, 1, 5),
       (4, 1, 6),
       (4, 2, 4),
       (4, 2, 6),
       (4, 3, 6),
       (4, 3, 7);