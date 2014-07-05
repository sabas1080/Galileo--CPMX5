/*
Ejercicio basado en ejemplo de nodejs para instapush
@sabasacustico Julio 2014
https://instapush.im/
*/

var instapush = require("instapush");
instapush.settings({
    id:'IDº1 del usuario', //ID que de asigna instapush
    secret:'clave secreta', //Clave secreta de la aplicacion
});

instapush.notify({"event":"Cafe","trackers":{"email":"Rico Cafe listo :)"}} ,function (err, response){
    console.log(response);
});
