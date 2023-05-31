-- CreateTable
CREATE TABLE `Datalogger` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `nominal` INTEGER NOT NULL,
    `waktuBeli` VARCHAR(191) NOT NULL,

    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
