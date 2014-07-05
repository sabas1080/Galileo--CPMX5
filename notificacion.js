var instapush = require("instapush");
instapush.settings({
    id:'id del usuario',
    secret:'clave secreta',
});

instapush.notify({"event":"Cafe","trackers":{"email":"Rico Cafe listo :)"}} ,function (err, response){
    console.log(response);
});
