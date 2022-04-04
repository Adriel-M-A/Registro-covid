create table localidad(cod_postal int primary key, nombre varchar(60));
create table centro_atencion(codigo serial primary key, nombre varchar(60), domicilio varchar(120),telefono varchar(20),cod_postal int);
alter table centro_atencion add constraint fk_centro_at_localidad foreign key(cod_postal) references localidad(cod_postal);
create table enfermeros(nro_documento int primary key, nombres varchar(80), apellido varchar(90), domicilio varchar(120),telefono varchar(20), matricula varchar(15), cod_postal int);
alter table enfermeros add constraint fk_enfermero_localidad foreign key(cod_postal) references localidad(cod_postal);
create table pacientes(nro_documento int primary key, nombres varchar(80), apellido varchar(90), fecha_nac Date, domicilio varchar(120), telefono varchar(20),cod_postal int, de_riesgo bit, vacunado bit, observaciones varchar(250));
alter table pacientes add constraint fk_paciente_localidad foreign key(cod_postal) references localidad(cod_postal);
alter table pacientes  ALTER COLUMN de_riesgo TYPE boolean using false;
alter table pacientes  ALTER COLUMN vacunado TYPE boolean using false;
create table tipo_vacuna(codigo serial primary key, nombre varchar(90), cant_dosis int);
create table vacunas(codigo serial primary key, lote varchar(10),fecha_venc date, cod_tipo_vacuna int, cantidad float);
alter table vacunas add constraint fk_vacuna_tipo_vac foreign key(cod_tipo_vacuna) references tipo_vacuna(codigo);
create table turno_vacuna(codigo serial primary key, fecha date, hora time,nro_doc_paciente int, nro_doc_enfermero int, asistio bit, cod_centro_a int, nro_dosis int, cod_vacuna int);
alter table turno_vacuna add constraint fk_turno_vacuna_paciente foreign key(nro_doc_paciente) references pacientes(nro_documento);
alter table turno_vacuna add constraint fk_turno_vacuna_enfermero foreign key(nro_doc_enfermero) references enfermeros(nro_documento);
alter table turno_vacuna add constraint fk_turno_vacuna_centro_at foreign key(cod_centro_a) references centro_atencion(codigo);
alter table turno_vacuna add constraint fk_turno_vacuna_vacuna foreign key(cod_vacuna) references vacunas(codigo);
alter table turno_vacuna ALTER COLUMN asistio TYPE boolean using false;

/* carga de informacion */

insert into localidad(cod_postal,nombre) values 
(9000,'Comodoro'),
(9100,'Trelew'),
(9103,'Rawson'),
(9105,'Gaiman'),
(9120, 'Puerto Madryn'),
(9200,'Esquel');
insert into tipo_vacuna(nombre, cant_dosis) values 
('pfizer-BiONTech',2),
('Moderna',2),
('Sputnik V',2);
insert into vacunas(codigo, lote, fecha_venc, cod_tipo_vacuna, cantidad) values 
(1,10,'2021/04/20',1,500),
(2,11,'2021/04/20',2,300),
(3,11,'2021/04/20',3,800);
insert into centro_atencion(codigo, nombre, domicilio, telefono, cod_postal) values 
(1,'centro atencion 1','Calle 1','205',9000),
(2,'centro atencion 2','Calle 2','206',9100),
(3,'centro atencion 3','Calle 3','207',9103),
(4,'centro atencion 4','Calle 4','208',9105),
(5,'centro atencion 5','Calle 5','209',9120);
insert into enfermeros(nro_documento, nombres, apellido, domicilio, telefono, matricula, cod_postal) values 
(30000000,'Jose','Peres','calle 0','2804000000','0000',9100),
(30000001,'Sofia','Lopez','calle 1','2804000001','0001',9100),
(30000002,'Marcos','Dante','calle 2','2804000002','0002',9100),
(30000003,'Nestor','Jones','calle 3','2804000003','0003',9103),
(30000004,'Albertina','Hernandez','calle 4','2804000004','0004',9103),
(30000005,'Julio','Roca','calle 5','2804000005','0005',9103);
insert into pacientes(nro_documento, nombres, apellido, fecha_nac, domicilio, telefono, cod_postal, de_riesgo, vacunado, observaciones) values 
(20000000,'Pepe','Peres','1970/02/05','calle 1','2804123456',9100,false,false,'observaciones'),
(20000001,'Coco','Lupin','1968/02/05','calle 2','2804456789',9100,true,false,'observaciones'),
(20000002,'Rolo','Lopes','1968/02/05','calle 3','2804147258',9100,false,false,'observaciones'),
(20000003,'Lidia','Lopes','1968/02/05','calle 4','2804258369',9103,true,false,'observaciones'),
(20000004,'Alfonso','Martines','1968/02/05','calle 5','2804258369',9103,true,false,'observaciones');
insert into turno_vacuna(codigo, fecha, hora, nro_doc_paciente, nro_doc_enfermero, asistio, cod_centro_a, nro_dosis, cod_vacuna) values 
(1,'2021/05/14','08:00',20000000,30000000,true,2,1,3),
(2,'2021/05/14','08:00',20000001,30000001,false,2,1,1),
(3,'2021/05/14','08:00',20000002,30000002,true,2,1,2),
(4,'2021/05/14','08:00',20000003,30000003,true,3,1,2),
(5,'2021/05/14','08:00',20000004,30000005,false,3,1,1);
