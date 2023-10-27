--1
CREATE or REPLACE TYPE Direccion as object
(calle VARCHAR2(25),
ciudad VARCHAR2(20),
codigo_post number(5));

--2
CREATE or REPLACE TYPE Persona as object 
(Codigo number(5),
nombre varchar(35),
direc Direccion,
fecha_nac date);

--3 y 4
CREATE TABLE ALUMNOS of PERSONA;
DECLARE
    dir Direccion := Direccion(NULL, NULL, NULL);
    dirb Direccion := Direccion(NULL, NULL, NULL);
    P Persona := Persona(NULL, NULL, dir, NULL);
    Pb Persona := Persona(NULL, NULL, dirb, NULL);
BEGIN
    dir.calle := 'La Mina,3';
    dir.ciudad := 'Guadalajara';
    dir.codigo_post := 19001;
    P.codigo := 1;
    P.nombre := 'Juan';
    P.direc := dir;
    P.fecha_nac := TO_DATE('10/11/1988', 'DD/MM/YYYY');

    dirb.calle := 'La Mena,5';
    dirb.ciudad := 'Soria';
    dirb.codigo_post := 15002;
    Pb.codigo := 2;
    Pb.nombre := 'Pepe';
    Pb.direc := dirb;
    Pb.fecha_nac := TO_DATE('16/05/1993', 'DD/MM/YYYY');

    -- Insertar datos en la tabla ALUMNOS
    INSERT INTO ALUMNOS VALUES (
        P.codigo,
        P.nombre,
        Direccion(P.direc.calle, P.direc.ciudad, P.direc.codigo_post),
        P.fecha_nac
    );

    INSERT INTO ALUMNOS VALUES (
        Pb.codigo,
        Pb.nombre,
        Direccion(Pb.direc.calle, Pb.direc.ciudad, Pb.direc.codigo_post),
        Pb.fecha_nac
    );

END;
/


