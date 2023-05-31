const fs = require('fs');
const fsPromises = require('fs').promises;
const path = require('path');

const logEvents = async (message, logName) => {
    const logItem = `${message}\n`;

    try {
        if (!fs.existsSync(path.join(__dirname, 'logs'))) {
            await fsPromises.mkdir(path.join(__dirname, 'logs'));
        }

        await fsPromises.appendFile(path.join(__dirname, 'logs', logName), logItem);
    } catch (err) {
        console.log(err);
    }
}

const logger = (req, res, next) => {
    logEvents(`\t${req.body.nominal} ${req.body.waktu}`, 'datalogger.log');
    console.log(`${req.method} ${req.path}`);
    next();
}

module.exports = { logger, logEvents };