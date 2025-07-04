select count(*) from producto

select count(*) from producto where estado = 'stock'

select * from producto where id_producto not in (select distinct id_producto from Detalle_venta)

select avg(cant_total) from (
	select id_producto, sum(cantidad) as cant_total from detalle_venta
	group by id_producto
) as sub

select id_vendedor, count(*) cantVentas from venta
group by id_vendedor
having count(*) = (
	select max(cantVentas) from (
		select count(*) cantVentas from venta
		group by id_vendedor
	) as sub
)

-- 5. Indique cual es la cantidad promedio de unidades vendidas de cada producto.

select * from detalle_venta

select id_producto, avg(cantidad) as cantVentas from detalle_venta
group by id_producto




select id_producto from detalle_venta
group by id_producto
having sum(cantidad) > 15

select id_vendedor, sum(dv.cantidad) vol_ventas from venta v
join detalle_venta dv on v.Nro_factura = dv.Nro_factura
group by id_vendedor
having sum(dv.cantidad) = (
	select max(suma) from (
		select sum(dv.cantidad) suma from venta v
		join detalle_venta dv on v.Nro_factura = dv.Nro_factura
		group by id_vendedor
	) as sub
)


select * from cliente
select * from detalle_venta
select * from direccion
select * from producto
select * from proveedor
select * from vendedor
select * from venta