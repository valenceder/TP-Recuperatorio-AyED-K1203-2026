# TP-Recuperatorio-AyED-K1203-2026

Valentín Tomás Cedermas

Comisión: K1203

El programa consiste en un menú con opciones, del cual cada una tendrá su función. Al ejecutarse, se despliegan las opciones disponibles. El usuario puede elegir una opción y llama a la función de la misma. Una vez que terminó de ejecutar (opción 0), el programa no guarda los datos, por lo tanto en la próxima ejecución del mismo arrancará en cero.

El PUP (posición única predecible) lo resolví haciendo la diferencia entre una clave y la clave inicial, por ejemplo si la clave inicial fuera 1 como en este caso, es la diferencia entre una clave y la clave 1. Este me dará la posición en la cual se ubica una clave, sin necesidad de una búsqueda en el disco. Por ejemplo, para modificar el socio, me ubico con fseek en dicha posición, en idsocio - 1, lo leo y se sobreescribe con fwrite. Para darlo de baja, es muy similar, accedo a dicha posición (idsocio - 1) y sobreescribo el registro con fwrite, en caso de que se dé la misma. Para el registro de pagos, también uso el PUP, accedo a la posición idsocio - 1, y luego lo inserto ordenado en el archivo de pagos, disponiendo de un archivo auxiliar. Y también para el reporte de cobranza, lo busco en dicha posición y lo traigo al recuento.

Para el corte de control, primero abro los dos archivos (socio y pagos), asigno un total y la cantidad de socios que pagaron. Luego, mientras que haya leído registros (1), obtengo el socio actual del que se busca la información, cuántas cuotas pagó y su total, y mientras siga leyendo registros, y el socio siga siendo el mismo, sumo la cantidad de cuotas pagadas y el total (usando la struct de Pagos), cuando se pasa al siguiente socio es cuando se produce el corte. Busco el nombre por PUP, y su actividad. Al final se muestra por pantalla, el total recaudado es la sumatoria del total de los socios, y la cantidad de socios que pagaron.
