CREATE  TABLE `FeedType` (
  `ftyp_id` VARCHAR(45) NOT NULL ,
  PRIMARY KEY (`ftyp_id`) )

CREATE  TABLE `FeedHistory` (
  `feed_id` INT NOT NULL ,
  `feed_dateTime` VARCHAR(45) NULL ,
  `feed_durationMin` INT NULL ,
  `feed_type` VARCHAR(45) NULL ,
  PRIMARY KEY (`feed_id`) ,
  INDEX `fk_FeedHistory_FeedTYpe` (`feed_type` ASC) ,
  CONSTRAINT `fk_FeedHistory_FeedTYpe`
    FOREIGN KEY (`feed_type` )
    REFERENCES `mydb`.`FeedType` (`ftyp_id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)

CREATE  TABLE `FeedConfig` (
  `fcfg_timeBetween` INT NOT NULL ,
  `fcfg_alertActive` INT NULL ,
  `fcfg_version` INT NULL ,
  PRIMARY KEY (`fcfg_timeBetween`) )

SET AUTOCOMMIT=0;
INSERT INTO `FeedType` (`ftyp_id`) VALUES ('Left');
INSERT INTO `FeedType` (`ftyp_id`) VALUES ('Right');
