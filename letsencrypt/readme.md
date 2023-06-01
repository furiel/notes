# Manually renew cert

```
# certbot certonly --manual
Saving debug log to /var/log/letsencrypt/letsencrypt.log
Please enter the domain name(s) you would like on your certificate (comma and/or
space separated) (Enter 'c' to cancel): ...

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
An RSA certificate named ... already exists. Do you want to
update its key type to ECDSA?
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
(U)pdate key type/(K)eep existing key type: k
Renewing an existing certificate for ...

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Create a file containing just this data:

<data>

And make it available on your web server at this URL:

http://.../.well-known/acme-challenge/<file>

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Press Enter to Continue

Successfully received certificate.
Certificate is saved at: /etc/letsencrypt/live/.../fullchain.pem
Key is saved at:         /etc/letsencrypt/live/.../privkey.pem
This certificate expires on ....
These files will be updated when the certificate renews.

NEXT STEPS:
- This certificate will not be renewed automatically. Autorenewal of --manual certificates requires the use of an authentication hook script (--manual-auth-hook) but one was not provided. To renew this certificate, repeat this same certbot command before the certificate's expiry date.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
If you like Certbot, please consider supporting our work by:
 * Donating to ISRG / Let's Encrypt:   https://letsencrypt.org/donate
 * Donating to EFF:                    https://eff.org/donate-le
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
```

Inside the container:

```
mkdir -p /var/lib/nginx/.well-known/acme-challenge
cd /var/lib/nginx/.well-known/acme-challenge
echo "<data>" > <file>
```
