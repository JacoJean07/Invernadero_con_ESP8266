# Invernadero_con_ESP8266
En este proyecto se creó un programa el cual esta conectado del arduino a una base de datos en Firebase y luego se muestra por medio de una pagina web que funciona por medio de XAMPP

aqui un video del funcionamiento entre otras cosas: https://www.youtube.com/watch?v=sbVuvay6lNs

como punto importante la carpeta example contiene todo el html, css y javascript para el proyecto, si se va a levantar un servidor con xampp no olvidarse de ponerlo en la carpeta htpdocs

en el archivo de pagina_usuario.html y pagina_invitado.html tiene que ir al inicio del script y poner sus credenciales de firebase para que se pueda conectar a la base de datos, justamente en " var firebaseConfig = ". si no se ponen las credenciales de su firebase no se podrá continuar con el proyecto

en el archivo .ino de arduino se tiene que instalar las librerías necesarias y luego igual cambiar ciertas credenciales para que conecte con firebase.
