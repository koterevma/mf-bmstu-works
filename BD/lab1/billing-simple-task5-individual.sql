DROP VIEW IF EXISTS T1;

CREATE VIEW T1 AS
SELECT currency, SUM(sum) as sum, COUNT(*) AS count
FROM `billing`
GROUP BY currency
ORDER BY count DESC,
    sum DESC;

SELECT *
FROM T1;

SELECT @maxcur := currency
FROM T1
WHERE T1.count = (
    SELECT MAX(count)
    FROM T1
);

SELECT @mincur := currency
FROM T1
WHERE T1.count = (
    SELECT MIN(count)
    FROM T1
);

INSERT INTO `billing`(
  `payer_email`,
  `recipient_email`,
  `sum`,
  `currency`,
  `billing_date`,
  `comment`
)
SELECT  `payer_email`,
        `recipient_email`,
        `sum`,
        @maxcur AS currency,
        `billing_date`,
        `comment`
FROM
`billing`
WHERE currency IN (@mincur);

SELECT currency, SUM(sum) as sum, COUNT(*) AS count
FROM `billing`
GROUP BY currency
ORDER BY count DESC,
    sum DESC;
