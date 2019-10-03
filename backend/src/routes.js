const express = require("express");

const routes = express.Router();

routes.get('/datas', (req, res) =>{
    res.send('Olá');
})
routes.post('/datas', (req, res) =>{
    console.log(req);
    res.send('Recebendo...');
})

module.exports = routes;