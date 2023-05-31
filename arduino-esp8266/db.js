const {PrismaClient} = require('@prisma/client')
const prisma = new PrismaClient()

const logData = async (nominal, waktuBeli) => {

    await prisma.$queryRaw`INSERT INTO datalogger VALUES (NULL, ${nominal}, ${waktuBeli})`
    .then(async () => {
        await prisma.$disconnect()
      })
      .catch(async (e) => {
        console.error(e)
        await prisma.$disconnect()
        process.exit(1)
      })
}

const showData = async () => {
  const logData = await prisma.$queryRaw`SELECT * FROM datalogger`
  return logData
}

module.exports = {logData, showData}