
# OnIP

This is a **simple** c program to syncronize (at cloudflare) and notify yourself IP address changes.

## Requirements

* Cloudflare API token: to syncronize the IP.
* SuperAlert token: to get your self notified via phone.

### SuperAlert
You can download the app to get the token:
* [Appstore](https://apps.apple.com/es/app/superalert/id1576722040)
* [Playstore](https://play.google.com/store/apps/details?id=me.nullx.alerter)
## Environment Variables

To run this project, you will need to add the following environment variables to your .env file

```sh
export CLOUDFLARE_ZONE_ID=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
export CLOUDFLARE_DNS_RECORD_ID=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
export CLOUDFLARE_BEARER_TOKEN=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
export CLOUDFLARE_RECORD_TYPE=A
export CLOUDFLARE_RECORD_NAME=xxx.xxxxx.com
export CLOUDFLARE_ZONE_NAME=xxxxx.com
export CLOUDFLARE_RULE_PROXIED=1
export CLOUDFLARE_RULE_TTL=1
export CLOUDFLARE_RULE_LOCKED=1
export CLOUDFLARE_RULE_PROXIABLE=1
export CLOUDFLARE_RULE_AUTO_ADDED=0
export CLOUDFLARE_RULE_MANAGED_BY_APPS=0
export CLOUDFLARE_RULE_MANAGED_BY_ARGO_TUNNEL=0
export MYSQL_HOST=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
export MYSQL__PORT=3306
export MYSQL_USER=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
export MYSQL_PWD=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
export MYSQL_DB=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

export SUPERALERT_BEARER_TOKEN="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
export SUPERALERT_KEY="XXX"
```

  
## Installation

### Clone
```bash
git clone <repo_uri>
cd <repo_uri>
  ```
### Build

```bash
make init
make build
```

## Usage

```bash
❯ ./build/onip      
14:11:00 INFO  src/main.c:11: ======= STARTING =======
14:11:00 INFO  src/lib/environment.c:32: Loading environment variables
14:11:00 DEBUG src/lib/environment.c:39: Found 14 environment variables
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_ZONE_ID
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_DNS_RECORD_ID
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_BEARER_TOKEN
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_RECORD_TYPE
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_RECORD_NAME
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_ZONE_NAME
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var CLOUDFLARE_RULE_PROXIABLE
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var SUPERALERT_BEARER_TOKEN
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var SUPERALERT_KEY
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var MYSQL_HOST
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var MYSQL_DB
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var MYSQL_USER
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var MYSQL_PWD
14:11:00 DEBUG src/lib/environment.c:51: Trying to load environment var MYSQL__PORT
14:11:00 DEBUG src/lib/environment.c:170: Loaded 14 environment variables
```

  