DROP TABLE IF EXISTS students;

CREATE TABLE IF NOT EXISTS `students` (
    `id` int(11) NOT NULL AUTO_INCREMENT,
    `FIO` varchar(50) NOT NULL,
    `group_` varchar(10) NOT NULL,  -- With _ sign because group is reserved keyword
    `d1` TINYINT NOT NULL,
    `d2` TINYINT NOT NULL,
    `d3` TINYINT NOT NULL,
    `d4` TINYINT NOT NULL,
    `d5` TINYINT NOT NULL,
    `d6` TINYINT NOT NULL,
    `d7` TINYINT NOT NULL,
    `d8` TINYINT NOT NULL,
    `d9` TINYINT NOT NULL,
    PRIMARY KEY (`id`)
)
