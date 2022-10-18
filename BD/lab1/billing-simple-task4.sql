SELECT *
FROM billing
WHERE payer_email IS NULL
    OR payer_email = ''
    OR recipient_email IS NULL
    OR recipient_email = ''
