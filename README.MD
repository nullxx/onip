
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
export FULL_FILE_NAME=data/ipstored
export DIRECTORY=data
export FILE_NAME=ipstored
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

export SUPERALERT_BEARER_TOKEN="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
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
14:28:35 INFO  src/main.c:11: ======= STARTING =======
14:28:35 INFO  src/lib/environment.c:25: Loading environment variables
14:28:35 DEBUG src/lib/environment.c:31: Found 11 environment variables
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var FULL_FILE_NAME
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var DIRECTORY
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var FILE_NAME
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_ZONE_ID
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_DNS_RECORD_ID
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_BEARER_TOKEN
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_RECORD_TYPE
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_RECORD_NAME
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_ZONE_NAME
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var CLOUDFLARE_RULE_PROXIABLE
14:28:35 DEBUG src/lib/environment.c:40: Trying to load environment var SUPERALERT_BEARER_TOKEN
14:28:35 DEBUG src/lib/environment.c:109: Loaded 11 environment variables
14:28:35 DEBUG src/main.c:14: FULL_FILE_NAME: data/ipstored
14:28:35 DEBUG src/main.c:23: Last IP (saved): 81.44.87.111
```

  