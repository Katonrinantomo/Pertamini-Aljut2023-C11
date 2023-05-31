const express = require('express');
const app = express();
const {logData, showData} = require('./db')
const PORT = process.env.PORT || 3500;
const { logger } = require('./logEvents');

app.use(express.urlencoded({extended: false}));
app.use(express.json());
app.use(logger);
app.set('view engine', 'ejs')

app.get('^/$|/index(.html)?', async (req, res) => {
    const log = await showData()
    res.render("index", { log })
})

app.post('/', async (req, res) => {
    console.log(req.body)
    if(req.get('User-Agent')=='ESP8266HTTPClient') {
        console.log(req.get('User-Agent'))
        console.log(req.body)
        await logData(req.body.nominal, req.body.waktu)
        res.sendStatus(200)
    }
})

app.all('*', (req, res) => {
    res.status(404);
    if(req.accepts('html')) {
        res.sendFile(path.join(__dirname, 'views', '404.html'));
    } else if(req.accepts('json')) {
        res.json({error: "404 Not Found"});
    } else {
        res.type('txt').send("404 Not Found");
    }
})
app.listen(PORT, ()=> console.log(`Server is running on http://localhost:${PORT}`))