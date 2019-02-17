CREATE  TABLE `FeedHistory` (
  `feed_id` INT NOT NULL ,
  `feed_dateTime` VARCHAR(45) NULL ,
  `feed_durationMin` INT NULL ,
  `feed_type` VARCHAR(45) NULL ,
  PRIMARY KEY (`feed_id`) )

CREATE  TABLE `FeedConfig` (
  `fcfg_timeBetween` INT NOT NULL ,
  `fcfg_alertActive` INT NULL ,
  `fcfg_version` INT NULL ,
  PRIMARY KEY (`fcfg_timeBetween`) )
