# Imitated Blockchain by Martynas Jašinskas

- [Setup](setup)
- [Changelog](changelog)
- [Program output](program-output)

## Setup

In order to run this block chain, you have to:  

1.) Download this repository and build it with:
```bash
make build
```
2.) Run the program with:
```Bash
./program
```
3.) Wait for initial generation of user profile and transaction pool:
```Bash
GENERATING USERS...
VALIDATING PUBLIC KEYS...
CREATING A TRANSACTION POOL...
VALIDATING TRANSACTION POOL INTEGRETY...

MINING A GENESIS BLOCK...
```
4.) Choose whether you want to mine additional blocks:
```Bash
Ar kasti nauja blocka?  y/n: y

MINING A BLOCK...
DONE!... PERFORMING TRANSACTIONS...
LOGGING THE BLOCK...
```
5.) Inspect the block outputs in the ```logs/``` folder. Here is an example:
<details>
  <summary>Click to expand!</summary>
  
  ```
    BLOCK: 0
  --------------------------------------------------

  BLOCK HASH: 00035e5e0b2117650b2117658f94b6978f94b697a5dfff6ba5dfff6bffa0058c
  PREVIOUS BLOCK HASH: sveiki, kaip sekasi?
  TIMESTAMP: 2021-10-23 18:15:37
  NUMBER OF TRANSACTIONS: 100
  DIFFICULTY: 3
  MERKEL ROOT HASH: 4998741cd30038b5d30038b531195fec31195fec8cf449b18cf449b18cdfa6f3
  VERSION: 0.1
  NONCE: 6668
  --------------------------------------------------

  BLOCK TRANSACTIONS


  ID: 3173cebe49954ddf49954ddfb99892c7b99892c710952c4210952c428d67713a
  SENDER PUBLIC KEY: 92f3277493089130930891307ee29bd37ee29bd30072bf740072bf74f8ef5356
  RECIPIENT PUBLIC KEY: 4b586ec43564cafc3564cafcfe3c1cfdfe3c1cfdd2b785b6d2b785b6ee99a898
  SUM: 717680

  ID: 92f9cf67b5fe0a69b5fe0a693a8105fc3a8105fca158165ca158165c1b1a4b75
  SENDER PUBLIC KEY: 7d046f74adc9d670adc9d670b39ae571b39ae571fbd72cd6fbd72cd6edafc1f4
  RECIPIENT PUBLIC KEY: 6d0c6f741dc466701dc46670249f2be5249f2be503387a4203387a42b5459760
  SUM: 110478
  
  ...
  ```
</details>

___
## Changelog

* [v0.2.1]() - initial working blockchain
* [v0.2.2]() - updated implementation with working merkel tree generation and multiple candidate system


## Program output
As shown in the [Setup](setup) part, the program outputs logs in which the summary of the block is presented.
```
BLOCK: 1
--------------------------------------------------

BLOCK HASH: 000588344c0759e64c0759e6ac7882a3ac7882a36dd4d7526dd4d752e3e7c614
PREVIOUS BLOCK HASH: 00035e5e0b2117650b2117658f94b6978f94b697a5dfff6ba5dfff6bffa0058c
TIMESTAMP: 2021-10-23 18:16:36
NUMBER OF TRANSACTIONS: 100
DIFFICULTY: 3
MERKEL ROOT HASH: 7c47163028b21cf828b21cf8c533f18dc533f18dc1e74b46c1e74b46969de880
VERSION: 0.1
NONCE: 51030
--------------------------------------------------

BLOCK TRANSACTIONS


ID: f5c971c8edb38076edb380769b42eff79b42eff7ccfff1b1ccfff1b1d3e881cf
SENDER PUBLIC KEY: 54a1e3743041ea703041ea700efa23c50efa23c56111c8626111c8625f4ca940
RECIPIENT PUBLIC KEY: 42f82f7431c86a7031c86a703abf08713abf0871a28d0586a28d05863abc54a4
SUM: 577813

...
```

**Here you are able to see**:  
1.) The block number in the blockchain  
2.) The block hash  
3.) Previous block hash  
4.) The time stamp of the mined block  
5.) The number of transactions that this block holds  
6.) The difficulty target  
7.) The merkel tree root hash  
8.) The version of the block system  
9.) The nonce of the block hash  

**Further down you will see all the transactions of the block, which include**:  
1.) The transaction ID  
2.) Sender public key  
3.) Recipient public key  
4.) The ammount of currency sent  
