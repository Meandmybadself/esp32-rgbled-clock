const express = require('express');

const app = express();

const times = [
    new Date().setHours(7, 22, 0, 0),
    new Date().setHours(14, 52, 0, 0),
]

app.get('/', async (_req, res) => {

    const numOfSecondsUntilNextEvent = times.reduce((acc, time) => {
        const secondsUntilNextEvent = (time - Date.now()) / 1000
        if (secondsUntilNextEvent > 0 && secondsUntilNextEvent < acc.seconds) {
            return { seconds: secondsUntilNextEvent, time }
        }
        return acc
    }, { seconds: Infinity, time: null })

    if (numOfSecondsUntilNextEvent.seconds === Infinity) {
        return res.send(`${1000000}`)
    }

    return res.send(`${parseInt(numOfSecondsUntilNextEvent.seconds || 0)}`)
})

const port = process.env.PORT || 3000;

app.listen(port, () => {
    console.log(`🐶 service http://127.0.0.1:${port}/`);
})