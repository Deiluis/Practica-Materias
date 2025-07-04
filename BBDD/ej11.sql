USE ej11

CREATE TABLE Genero (
	Id INT not null primary key,
	NombGenero varchar(51) not null,
)

CREATE TABLE Director (
	Id INT not null primary key,
	NyA varchar(51) not null,
)

CREATE TABLE Pelicula (
	CodPel INT NOT NULL primary key,
	Titulo varchar(255) not null,
	Duracion INT not null,
	CodGenero INT not null,
	IdDirector INT not null,
	foreign key (CodGenero) references Genero (Id),
	foreign key (IdDirector) references Director (Id),
)

create table Ejemplar (
	NroEj int not null,
	CodPel int not null,
	Estado bit not null,
	primary key (NroEj, CodPel),
	foreign key (CodPel) references Pelicula (CodPel)
)

create table Cliente (
	CodCli int not null primary key,
	NyA varchar(51) not null,
	Direccion varchar(101) not null,
	Tel int,
	Email varchar(255) not null,
	Borrado bit not null
)

create table Alquiler (
	Id int not null primary key,
	NroEj int not null,
	CodPel int not null,
	CodCli int not null,
	FechaAlq Date not null,
	FechaDev Date,
	foreign key (NroEj, CodPel) references Ejemplar (NroEj, CodPel),
	foreign key (CodCli) references Cliente (CodCli),
)


insert into Cliente values 
(1, 'Juan Perez', 'Florencio Varela 1903', NULL, 'jperez@gmail.com', 0),
(2, 'Martín Castro', 'Arieta 6004', 1127436734, 'mcastro@gmail.com', 0),
(3, 'Mariana Robles', '25 de mayo 5600', 1423424353, 'mrobles@gmail.com', 0)

update cliente set borrado = 1 where CodCli = 3

insert into Genero values
(1, 'Comedia'),
(2, 'Terror'),
(3, 'Aventuras'),
(4, 'Romance'),
(5, 'Drama')


insert into Director values
(1, 'Francis Ford Coppola'),
(2, 'Terror'),
(3, 'Aventuras'),
(4, 'Romance'),
(5, 'Drama')



alter table Pelicula 
add new column Año INT not null




select * from Pelicula