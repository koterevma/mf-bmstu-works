CREATE TABLE `students` IF NOT EXISTS (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `FIO` varchar(50) NOT NULL,
    `group_` varchar(10) NOT NULL,  -- With _ sign because group is reserved keyword
    `d1` TINIINT NOT NULL,
    `d2` TINIINT NOT NULL,
    `d3` TINIINT NOT NULL,
    `d4` TINIINT NOT NULL,
    `d5` TINIINT NOT NULL,
    `d6` TINIINT NOT NULL,
    `d7` TINIINT NOT NULL,
    `d8` TINIINT NOT NULL,
    `d9` TINIINT NOT NULL,
    PRIMARY KEY (`id`)
)
