use ejericio1;
use ej1_ArticulosDeAlmacen;

select * from Proveedor
select Nombre from Proveedor where Ciudad = 'La Plata'

select * from Articulo
select CodArt from Articulo where Precio < 10

select * from Almacen
select Responsable from Almacen

select * from Provisto_Por
select CodMat from Provisto_Por where CodProv = 10 and CodMat not in (select CodMat from Provisto_Por where CodProv = 15)

select * from Tiene

select * from Material


select Nombre from Proveedor where Ciudad = 'Pergamino' and Nombre like '%perez'


select * from Compuesto_Por
select CodArt from Articulo where Precio > 1000 or CodArt in (select CodArt from Compuesto_Por where CodMat = 1)

select * from Proveedor where Ciudad = 'La Plata'

select CodMat, Descripcion from Material where CodMat in (
	select CodMat from Provisto_Por where CodProv in (
		select CodProv from Proveedor where Ciudad = 'Pergamino'
	)
)

select m.CodMat, Descripcion from Material m 
join Provisto_Por pp on m.codMat = pp.codMat
join proveedor p on pp.codProv = p.codProv where p.ciudad = 'Pergamino'


select a.CodArt, Descripcion, Precio from Articulo a
join Tiene t on a.CodArt = t.CodArt where t.NroAlmacen = 1


select m.Descripcion from Articulo a
join Compuesto_por cp on a.codArt = cp.codArt
join Material m on cp.codMat = m.codMat where a.codArt = 2


select distinct a.codArt, a.descripcion from Articulo a
join Compuesto_por cp on a.codArt = cp.codArt
join Provisto_por pp on cp.codMat = pp.codMat
join Proveedor p on p.codProv = pp.codProv 
where p.nombre like '%platense'


select p.CodProv, p.Nombre from proveedor p
join provisto_por pp on p.codProv = pp.codProv
join compuesto_por cp on cp.codMat = pp.codMat
join articulo a on a.codArt = cp.codArt
where a.precio > 400


select distinct alm.nro from almacen alm
join tiene t on t.NroAlmacen = alm.nro
join compuesto_por cp on cp.codArt = t.codArt
where cp.codMat = 1


-----------------------------------------------------


select p.* from proveedor p
join provisto_por pp on pp.codProv = p.codProv
join material m on m.codMat = pp.codMat
where p.ciudad = 'CABA'


select codProv, count(*) from provisto_por pp
group by pp.codProv



select p.* from proveedor p
where p.ciudad = 'CABA' and exists (
	select 1 from provisto_por pp
	where pp.codProv = p.codProv
	group by pp.codMat
	having count(*) = 1
)

select 1 from provisto_por pp
group by pp.codMat
having count(*) = 1

-----------------------------------------------------

select * from articulo where precio in (select max(precio) from articulo)

select * from articulo where precio in (select min(precio) from articulo)

select avg(precio) from articulo

select NroAlmacen, count(*) as cantArt from tiene
group by NroAlmacen
having count(*) = (
	select max(cantidad) from (
		select count(*) as cantidad from tiene
		group by NroAlmacen	
	) as sub
)


select codArt, count(*) as cantMat from Compuesto_Por
group by codArt
having count(*) >= 2

select codArt, count(*) as cantMat from Compuesto_Por
group by codArt
having count(*) = 2

select codArt, count(*) as cantMat from Compuesto_Por
group by codArt
having count(*) <= 2

select codArt, count(*) as cantMat from Compuesto_Por
group by codArt
having count(*) = (
	select count(*) from Material
)

select ciudad from proveedor where codProv in (
	select codProv from provisto_por
	group by codProv
	having count(*) = (
		select count(*) from Material
	)
)

select * from articulo
select * from Compuesto_Por
select * from proveedor
select * from provisto_por
select * from Material
select * from almacen
select * from tiene