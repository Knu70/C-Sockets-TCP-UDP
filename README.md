# C Sockets TCP UDP

El sensor puede ser de tres tipos, polución, temperatura o humedad. Esto se eligirá por pantalla además de pedir que se introduzca la ciudad y la medida. 

Una vez se recoge toda esta información se envía al servidor B mediante UDP y si todo llega correctamente el sensor recibe un OK del servidor B.

Cuando el servidor B recibe toda la información del sensor, la concatena en una cadena mensaje con el formato ipSensor:Ciudad:Sensor:Medida.

Si cumple los parámetros, se creará un socket TCP, se establecerá conexión con el servidor A y se enviará, recibiendo un OK del servidor A si todo llega correctamente.

<div align="center">
  <img src="https://github.com/road2root/C-Sockets-TCP-UDP/blob/main/modelo.png" width="500" />
</div>

