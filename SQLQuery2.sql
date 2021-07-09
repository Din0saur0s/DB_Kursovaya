-- Смены
CREATE TABLE Smeny
(
Smeny_id int PRIMARY KEY IDENTITY(1,1) NOT NULL,
DataStart date,
DataEnd date,
);
-- Строительные отряды
CREATE TABLE StrOtryady
(
StrOtrName NVARCHAR(50) NOT NULL,
LocationName NVARCHAR(100),
StrOtryad_Smena int REFERENCES Smeny (Smeny_id) ON DELETE SET DEFAULT,
StrOtr_id int PRIMARY KEY IDENTITY(1,1) NOT NULL,
);
-- Учебные группы студентов
CREATE TABLE Groups
(
 Group_id int PRIMARY KEY IDENTITY(1,1) NOT NULL,
 GroupName NVARCHAR(50) NOT NULL,
);
-- Студенты
CREATE TABLE Students
(
 StudBilet NVARCHAR(50) PRIMARY KEY NOT NULL,
 Familia NVARCHAR(50) NOT NULL,
 Imya NVARCHAR(50) NOT NULL,
 Otchestvo NVARCHAR(50),
 Student_StrOtr int REFERENCES StrOtryady (StrOtr_id) ON DELETE SET DEFAULT,
 Student_Group int REFERENCES Groups (Group_id) ON DELETE SET DEFAULT,
);
-- Работы
CREATE TABLE Works
(
Work_id int PRIMARY KEY IDENTITY(1,1) NOT NULL,
WorkName NVARCHAR(50),
Pay REAL,
Work_Smena int REFERENCES Smeny (Smeny_id) ON DELETE SET DEFAULT,
) go
--drop table works

-- Заполнение таблицы смен
INSERT INTO Smeny (DataStart,DataEnd)
VALUES ('2020-07-01', '2020-08-01'), ('2020-08-01', '2020-09-01')
GO
-- Заполнение таблицы стройотрядов
INSERT INTO StrOtryady (StrOtrName, LocationName, StrOtryad_Smena)
VALUES ('Офицеры','Москва',1),('Россияне','Санкт-Петербург',1),('Россияне','Красноуральск',2),('Опера','Красноуральск',2),('Офицеры','Красноуральск',2)
GO
-- Заполнение таблицы учебных групп
INSERT INTO Groups (GroupName)
VALUES ('АБВГ-1-19'),('АБВГ-2-19'),('АБВГ-3-19'),('КЛМН-1-19'),('КЛМН-2-19'),('ПРСТ-1-19'),('ПРСТ-2-19'),('ПРСТ-3-19'),('ПРСТ-4-19')
GO
-- Заполнение таблицы студентов
INSERT INTO Students (StudBilet, Familia, Imya, Otchestvo, Student_StrOtr, Student_Group)
VALUES ('19Б001','Вейдер','Дарт','Дарт',4,1),('19Б028','Балбес','Пётр','Петрович',3,4),('19Б062','Бывалый','Фёдор','Фёдорович',3,4),
('19Б090','Трус','Иван','Иванович',3,4),('19Б111','Штирлиц','Отто','',2,6),('19Б139','Романова','Екатерина','Алексеевна',1,1),
('19Б300','Красносолнышков','Владимир','',4,3),('19Б302','Вещий','Олег','',4,8),('19Б311','Романов','Пётр','Алекчеевич',1,2),
('19Б331','Грозный','Иван','Васильевич',4,5),('19Б333','Исаев','Максим','Максимович',2,6),('19Б340','Каренина','Анна','Аркадьевна',2,7),
('19Б346','Скайуокер','Люк','Энакинович',2,8),('19Б362','Морозова','Снежанна','',4,9),('19Б380','Привалов','Александр','Шурикович',1,9),
('19Б445','Чапаев','Василий','Иванович',1,4),('19Б517','Премудрая','Василиса','',1,6),('19Б533','Селезнёва','Алиса','Игоревна',2,7),
('19Б701','Пчёлкина','Юлия','Дмитриевна',3,3),('19Б808','Ульянов','Владимир','Ильич',4,1),('19Б893','Годунов','Борис','Фёдорович',3,7),
('19Б789','Столыпин','Пётр','Аркадьевич',1,2)
GO
-- Заполнение таблицы 
INSERT INTO Works (WorkName, Pay, Work_Smena)
VALUES ('Земляные работы',15000,1),('Дорожные работы',20000,2),('Подсобные работы',12500,1),('Отделочные работы',17000,2),('Сварочные работы',18000,1)
GO




SELECT distinct Familia, Pay, (SELECT distinct GroupName from Groups,
Students where Students.Student_Group=Group_id) as 
Gruppa from (select distinct * from Works join Smeny on Works.Work_Smena=Smeny.Smeny_id join StrOtryady on Smeny_id=StrOtryad_Smena join Students on StrOtr_id=Student_StrOtr join Groups on
Group_id=Student_Group) as aaaaa where
(Select * from Groups where GroupName='АБВГ-1-19')

go
select distinct  WorkName, pay from works, (select distinct Smeny_id from smeny, works where Smeny_id=Work_Smena) as Nachalo
from (select * from  Works join Smeny on Work_id=Work_Smena) as aaaaa
where  pay> 0--(select min(pay) from works )
-- максимальная оплата за вторую смену
select pay ,(select workname from works where Work_id>=1) as WorkName
from (select pay, WorkName from works where Work_Smena=2 ) as work
where pay=(select max(pay) from works)




SELECT distinct Familia, Pay, (SELECT distinct StrOtrName from StrOtryady, Students where Students.Student_StrOtr=StrOtr_id) from Students, works


-- Какие студенты к какому направлению относятся
SELECT Distinct Familia, GroupName,
CASE 
WHEN GroupName LIKE 'АБВГ%' THEN 'АБВГ'
WHEN GroupName LIKE 'КЛМН%' THEN 'КЛМН'
WHEN GroupName LIKE 'ПРСТ%' THEN 'ПРСТ'
end Napravleniya
FROM Students, Groups where Student_Group=Group_id order by Napravleniya;


use Cursach exec sys.sp_helpfile;

-- Какой студент какой группы находится
-- в каком стройотряде
CREATE VIEW st_gr_ot AS
SELECT S.Familia as Familia, G.GroupName as Gruppa, SO.StrOtrName as StroyOtryad
FROM Groups G, Students S, StrOtryady SO
WHERE G.Group_id=S.Student_Group AND S.Student_StrOtr=SO.StrOtr_id;

SELECT * FROM st_gr_ot ORDER BY Familia;


--
SELECT S.Familia FROM Students S;

SELECT s.familia, so.strotrname from Students s, StrOtryady so where so.StrOtr_id=s.Student_StrOtr;

/*
SELECT Works.WorkName, Works.Pay, Smeny.Smeny_id
(SELECT * FROM (Works JOIN Smeny on Work_Smena=Smeny_id)
FROM )
from works, smeny
WHERE EXISTS Works.Pay >= (SELECT AVG(Works.Pay));
*/
--Works, Smeny

/*
Select (select Works.WorkName from Works),(select Works.Pay from Works), (SELECT Smeny_id from Smeny, Works where Work_Smena=Smeny_id) 
from (select Works.WorkName, Works.Pay, Smeny.Smeny_id from Works, Smeny where Works.Pay>AVG(Pay)) as workname
WHERE StrOtryady.LocationName = (SELECT StrOtryady.LocationName From StrOtryady where LocationName = 'Красноуральск')
;
*/

-- Название работ, оплачиваемых выше среднего, их оплаты и рабочие смены
select works.WorkName, works.Pay, (select smeny.Smeny_id from smeny as Smena where Work_Smena=Smeny_id)
from (Works join Smeny on Work_Smena=Smeny_id)
Where pay > (select avg(pay) from works);

-- Название работ, оплачиваемых ниже среднего, их оплаты и рабочие смены
select works.WorkName, works.Pay, smeny.Smeny_id
from (Works join Smeny on Work_Smena=Smeny_id)
Group by workname, pay, Smeny_id Having pay < (select avg(pay) from works);

-- Работы, прибыльнее среднего во вторую смену
SELECT	Works.WorkName, Works.Pay FROM Works WHERE  Works.Pay > any (SELECT avg(Works.Pay) FROM Works, Smeny where Smeny_id=2 and Smeny_id=Work_Smena )

--drop table Smeny, StrOtryady, Groups, Students, Works 


CREATE INDEX i_group_name on Groups (GroupName)
CREATE INDEX i_student_familiya ON Students(Familia)
CREATE INDEX i_StrOtryad_Location ON StrOtryady(LocationName)
CREATE INDEX i_work_name ON Works (WorkName)
-- ТРИГГЕРЫ
CREATE TABLE Timing
(
id INT PRIMARY KEY IDENTITY NOT NULL,
StudBilet_T NVARCHAR(50) NOT NULL,
Operation NVARCHAR(50) NOT NULL,
OperTime DATETIME NOT NULL DEFAULT GETDATE()
)GO



CREATE TRIGGER tr_add on [dbo].[Students] AFTER INSERT AS 
INSERT INTO Timing (StudBilet_T, Operation)
SELECT StudBilet, 'Добавлен студент ' + Familia FROM inserted
GO

CREATE TRIGGER tr_upd on [dbo].[Students] AFTER UPDATE AS 
INSERT INTO Timing (StudBilet_T, Operation)
SELECT StudBilet, 'Обновлён студент ' + Familia FROM inserted
GO

CREATE TRIGGER tr_del on [dbo].[Students] AFTER delete AS 
INSERT INTO Timing (StudBilet_T, Operation)
SELECT StudBilet, 'Удалён студент ' + Familia FROM deleted
GO
--CREATE TRIGGER tr_add
drop trigger tr_del
DROP PROCEDURE insertsmena
DROP PROCEDURE updatesmena
DROP PROCEDURE deletesmena
go

-- Добавляем / обновляем / удаляем смену по дате начала (все смены длятся одмнаковое количество дней)
CREATE PROCEDURE INSERTsmena (@DataStart DATE, @DataEnd DATE) AS BEGIN INSERT INTO Smeny (DataStart,DataEnd) VALUES ( @DataStart, @DataEnd) END;
GO

CREATE PROCEDURE UPDATEsmena (@StartOld date,@DataStart DATE, @DataEnd DATE) AS BEGIN UPDATE Smeny SET DataStart=@DataStart, DataEnd=@DataEnd 
WHERE @StartOld=DataStart END;
GO

CREATE PROCEDURE DELETEsmena (@DataStart date) AS BEGIN DELETE Smeny WHERE DataStart=@DataStart END;
GO


EXEC INSERTsmena '2020-05-01','2020-06-01';
EXEC UPDATEsmena '2020-05-01', '2020-06-01', '2020-07-01';
EXEC DELETEsmena '2020-06-01';


-- Добавляем / обновляем / удаляем строительные отряды по их названию
CREATE PROCEDURE INSERTstrotr (@StrOtrName NVARCHAR(50), @LocationName NVARCHAR(50), @StrOtryad_Smena int) AS BEGIN INSERT INTO StrOtryady(StrOtrName, LocationName, StrOtryad_Smena) VALUES (@StrOtrName, @LocationName, @StrOtryad_Smena) END;
GO

CREATE PROCEDURE UPDATEstrotr (@StrOtrName NVARCHAR(50), @LocationName NVARCHAR(50), @StrOtryad_Smena int) AS BEGIN UPDATE StrOtryady SET LocationName=@LocationName, StrOtryad_Smena=@StrOtryad_Smena
where StrOtrName=@StrOtrName END;
GO

CREATE PROCEDURE DELETEstrotr (@StrOtrName NVARCHAR(50)) AS BEGIN DELETE StrOtryady WHERE StrOtrName=@StrOtrName END;
GO

EXEC INSERTstrotr 'Джедаи', 'Москва', 1;
EXEC UPDATEstrotr 'Джедаи', 'Москва', 2;
EXEC DELETEstrotr 'Джедаи';

-- Добавляем / обновляем / удаляем учебные группы студентов их названию
CREATE PROCEDURE INSERTgroup (@GroupName NVARCHAR(50)) AS BEGIN INSERT INTO Groups (GroupName) VALUES (@GroupName) END;
GO

CREATE PROCEDURE UPDATEgroup (@GroupName NVARCHAR(50), @GroupName_new NVARCHAR(50)) AS BEGIN UPDATE Groups SET GroupName=@GroupName_new
where GroupName=@GroupName END;
GO

CREATE PROCEDURE DELETEgroup (@GroupName NVARCHAR(50)) AS BEGIN DELETE Groups WHERE GroupName=@GroupName END;
GO

EXEC INSERTgroup 'СИТХ-01-23';
EXEC UPDATEgroup 'СИТХ-01-23','КОТЫ-02-20';
EXEC DELETEgroup 'КОТЫ-02-20';



-- Добавляем / обновляем / удаляем студентов по студ.билету

CREATE PROCEDURE INSERTstudent (@StudBilet NVARCHAR(50), @Familia NVARCHAR(50), @Imya NVARCHAR(50), @Otchestvo NVARCHAR(50), @StrOtrName NVARCHAR(50), @GroupName NVARCHAR(50)) AS BEGIN
INSERT INTO Students(StudBilet, Familia, Imya, Otchestvo, Student_StrOtr, Student_Group) VALUES(@StudBilet, @Familia, @Imya, @Otchestvo, (select distinct Students.Student_StrOtr from students, StrOtryady where @StrOtrName=StrOtrName and StrOtr_id=Student_StrOtr),
(select distinct Groups.Group_id from Groups, Students where @GroupName=GroupName and Group_id=Student_Group)) 
END;
GO
--DROP PROCEDURE  insertstudent
--DROP PROCEDURE  updatestudent
--DROP PROCEDURE  deletestudent

CREATE PROCEDURE UPDATEstudent (@StudBilet NVARCHAR(50), @Familia NVARCHAR(50), @Imya NVARCHAR(50), @Otchestvo NVARCHAR(50), @StrOtrName NVARCHAR(50), @GroupName NVARCHAR(50)) AS BEGIN
UPDATE Students SET  Familia=@Familia, Imya=@Imya, Otchestvo=@Otchestvo, Student_StrOtr=(select distinct Students.Student_StrOtr from students, StrOtryady where StrOtrName=@StrOtrName and StrOtr_id=Student_StrOtr),
Student_Group=(select distinct Groups.Group_id from Groups, Students where @GroupName=GroupName and Group_id=Student_Group) where @StudBilet=StudBilet
END;
GO--HOIHIUHUIGOIGOUGYUFUYTFYTNYIUHNIUP						UMOYWXUWOHUOWZZOUQBOQ			HE RABOTAET

CREATE PROCEDURE DELETEstudent (@StudBilet NVARCHAR(50)) AS BEGIN DELETE Students WHERE StudBilet=@StudBilet END;
GO

EXEC INSERTstudent '19Б198','Куджо','Джотаро','','Опера','АБВГ-1-19';
EXEC UPDATEstudent '19Б198','Джостар','Джозеф','Джорджевич','Офицеры','АБВГ-2-19';
EXEC DELETEstudent '19Б198';

-- Добавляем / обновляем / удаляем работы по их названию
CREATE PROCEDURE INSERTwork ( @WorkName NVARCHAR(50), @Pay REAL, @Smeny_id INT) AS BEGIN INSERT INTO Works (WorkName,Pay,Work_Smena)
VALUES (@WorkName, @Pay, @Smeny_id) END;
GO

CREATE PROCEDURE UPDATEwork ( @WorkName NVARCHAR(50), @Pay REAL, @Smeny_id INT) AS BEGIN UPDATE Works SET Pay=@Pay, Work_Smena=@Smeny_id
WHERE WorkName=@WorkName END;
GO

CREATE PROCEDURE DELETEwork (@WorkName NVARCHAR(50)) AS BEGIN DELETE Works WHERE WorkName=@WorkName END;
GO

EXEC INSERTwork 'Мешки ворочать', 25000, 1;
EXEC UPDATEwork 'Мешки ворочать',22500,2;
EXEC DELETEwork 'Мешки ворочать';
--DROP PROCEDURE  insertstudent

/*CREATE PROCEDURE TimeCheck (@Smeny_id INT, @tDataStart DATE, @tDataEnd DATE) AS BEGIN
BEGIN TRANSACTION
UPDATE Smeny SET DataStart=@tDataStart, DataEnd=@tDataEnd WHERE Smeny_id=@Smeny_id;
IF (@tDataEnd<@tDataStart) ROLLBACK;
ELSE COMMIT TRANSACTION
END;
GO
DROP PROCEDURE studCheck
EXEC TimeCheck 1,'2021-01-01','2019-01-01'*/

-- Проверка отсутствия цифр в ФИО
CREATE PROCEDURE dbo.StudCheck (@StudBilet NVARCHAR(50), @Familia NVARCHAR(50), @Imya NVARCHAR(50), @Otchestvo NVARCHAR(50)) AS BEGIN
BEGIN TRANSACTION
UPDATE Students SET Familia=@Familia, Imya=@Imya, Otchestvo=@Otchestvo WHERE StudBilet=@StudBilet;
--IF (ISNUMERIC(@Familia)=1 OR ISNUMERIC(@Imya)=1 OR ISNUMERIC(@Otchestvo)=1) ROLLBACK;
if ( @Familia like '%[0123456789]%' or @Imya like '%[0123456789]%' or @Otchestvo like '%[0123456789]%') ROLLBACK;
ELSE COMMIT TRANSACTION
END;
GO
--
EXEC StudCheck '19Б362','К0стерева','Дарья','Викторовна';
exec DELETEstudent '19Б000';
select familia from Students where Familia NOT like '%[0123456789]%'
--
SELECT COUNT (W.WorkName) FROM  Smeny S,Works W WHERE W.Work_Smena=1;
SELECT COUNT(WORKNAME) FROM Works, Smeny WHERE Work_Smena LIKE '%'
GO
--

-- Зарплата в сменах, где количество работников меньше половины их полного количества, увеличивается на 1234 рубля
CREATE PROCEDURE payCursor AS BEGIN DECLARE @WorkName NVARCHAR(50), @Pay REAL,@Work_Smena INT,@Studbilet INT
DECLARE P_Cur CURSOR FOR SELECT Works.WorkName, Works.Pay, Works.Work_Smena FROM Works OPEN P_Cur
FETCH NEXT FROM P_Cur INTO @WorkName, @Pay, @Work_Smena
WHILE @@FETCH_STATUS = 0
BEGIN IF (SELECT COUNT(@WorkName) FROM Works , SMENY WHERE Works.Work_Smena=@Work_Smena) < (SELECT COUNT(@WorkName)/2 FROM Works, Smeny WHERE Work_Smena LIKE '%')
UPDATE WORKS SET Pay=Pay + 1234
WHERE WorkName=@WorkName
FETCH NEXT FROM P_Cur INTO @WorkName, @Pay, @Work_Smena
END
CLOSE P_CUR
DEALLOCATE P_Cur
END
GO

--DROP PROCEDURE payCursor

EXEC payCursor

SELECT S.Familia, W.WORKNAME, W.WORK_SMENA, W.Pay  FROM WORKS W, STUDENTS S, Smeny SM, StrOtryady ST WHERE Work_Smena=Smeny_id AND Smeny_id=StrOtryad_Smena AND StrOtr_id=Student_StrOtr

GO

--скалярная функция - итоговый заработок студентов
CREATE FUNCTION dbo.PaySum (@pay real) RETURNS REAL
AS BEGIN
DECLARE @RESULT REAL, @studbilet NVARCHAR(50)
SELECT @RESULT=SUM(Pay)  FROM WORKS W, STUDENTS S, Smeny SM, StrOtryady ST WHERE Work_Smena=Smeny_id AND Smeny_id=StrOtryad_Smena AND StrOtr_id=Student_StrOtr 
return @result;
END;

--drop function dbo.PaySum

SELECT distinct Familia, Oplata=sum(pay)  FROM WORKS, STUDENTS, Smeny, StrOtryady WHERE Work_Smena=Smeny_id AND Smeny_id=StrOtryad_Smena AND StrOtr_id=Student_StrOtr group by familia
SELECT distinct Familia, Oplata=dbo.paysum(@pay)  FROM WORKS, STUDENTS, Smeny, StrOtryady WHERE Work_Smena=Smeny_id AND Smeny_id=StrOtryad_Smena AND StrOtr_id=Student_StrOtr group by familia



go


--табличная функция (ссылается на пункт 6, ФИО, не содержащие цифр)
CREATE FUNCTION [dbo].[f_table]
(@STROTR INT)
RETURNS TABLE AS RETURN
(SELECT * FROM STUDENTS WHERE @STROTR=STUDENT_STROTR)
GO
--DROP FUNCTION [dbo].[f_table]
CREATE PROCEDURE dbo.StudCheckTable (@StudBilet NVARCHAR(50), @Familia NVARCHAR(50), @Imya NVARCHAR(50), @Otchestvo NVARCHAR(50)) AS BEGIN
BEGIN TRANSACTION
UPDATE Students SET Familia=@Familia, Imya=@Imya, Otchestvo=@Otchestvo WHERE StudBilet=@StudBilet;
--IF (ISNUMERIC(@Familia)=1 OR ISNUMERIC(@Imya)=1 OR ISNUMERIC(@Otchestvo)=1) ROLLBACK;
if ( @Familia like '%[0123456789]%' or @Imya like '%[0123456789]%' or @Otchestvo like '%[0123456789]%') ROLLBACK;
ELSE COMMIT TRANSACTION;
IF ( @Familia  not like '%[0123456789]%' and @Imya not like '%[0123456789]%' and @Otchestvo not like '%[0123456789]%') 
select * from [dbo].[F_TABLE] (1)
END;
GO
EXEC dbo.StudCheckTable '19Б362','иван0в','Иван','Иван0вич';
select familia, imya, otchestvo from f_table
select * from Students where Familia NOT like '%[0123456789]%'

use Cursach
CREATE LOGIN ADDmin WITH PASSWORD='1'
CREATE USER ADDmin FOR LOGIN ADDmin;
CREATE LOGIN ADDmax WITH PASSWORD='admin'
CREATE USER ADDmax FOR LOGIN ADDmax;
--DROP ROLE UZVER
CREATE ROLE ODMEN;
CREATE ROLE UZVER;


GRANT SELECT, UPDATE, INSERT, DELETE ON Students TO ODMEN;
GO
GRANT SELECT, UPDATE, INSERT, DELETE ON StrOtryady TO UZVER;
GO

REVOKE SELECT ON Students FROM ODMEN;
REVOKE INSERT ON StrOtryady FROM UZVER;

EXECUTE AS USER ='ADDmin'
SELECT* FROM Students;  
GO 

--Предоставить привилегии на роль