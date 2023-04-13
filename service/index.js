const express = require('express');

const app = express();

const times = [
    new Date().setHours(7, 22, 0, 0),
    new Date().setHours(14, 52, 0, 0),
]

app.get('/', (_req, res) => res.send('<h1>ESP3D RGB LED API service</h1>'));

app.get('/bus', async (_req, res) => {

    const numOfSecondsUntilNextEvent = times.reduce((acc, time) => {
        const secondsUntilBus = (time - Date.now()) / 1000
        if (secondsUntilBus > 0 && secondsUntilBus < acc.seconds) {
            return { seconds: secondsUntilBus, time }
        }
        return acc
    }, { seconds: Infinity, time: null })

    return res.send(`${parseInt(numOfSecondsUntilNextEvent.seconds || 0)}`)
})

const port = process.env.PORT || 3000;

app.listen(port, () => {
    console.log(`🐶 service http://127.0.0.1:${port}/`);
})