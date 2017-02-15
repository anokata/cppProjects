BEGIN TRANSACTION;

DROP TABLE IF EXISTS [Items];
DROP TABLE IF EXISTS [Inventory];

CREATE TABLE [Items]
(      [ItemID] INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
       [Name] TEXT,
       [Count] INTEGER,
       [ImagePath] TEXT
);

CREATE TABLE [Inventory]
(
   [ItemID] INTEGER NOT NULL,
   [X] INTEGER NOT NULL,
   [Y] INTEGER NOT NULL,

   PRIMARY KEY ("X","Y"),
   FOREIGN KEY ([ItemID]) REFERENCES [Items] ([ItemID]) 
		ON DELETE NO ACTION ON UPDATE NO ACTION
);

INSERT INTO Items VALUES(null,'apple',1,'./apple.jpg');
INSERT INTO Items VALUES(null,'apple',2,'./apple.jpg');
INSERT INTO Inventory VALUES(1, 0, 0);
INSERT INTO Inventory VALUES(2, 1, 1);

COMMIT;
