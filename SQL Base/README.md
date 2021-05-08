# Database with web interface
Project realized in 2019 with Théo MATRICON, Maxime ROSAY.

[SGBD_2019.pdf](SGBD_2019.pdf) is a French report of this project describing more precisely the work done and explained below.

## Project description
This project concerns the modeling, creation and implementation of a database and includes two main parts: 
- Web interface and database management
- Database and server deployment 

## Pre-requesties :
- [MySQL](https://dev.mysql.com/downloads/mysql/) version 8.0.1
- [Node.js](https://nodejs.org/en/) version 12.13.1 LTS

## Database Managment
The managment of the database is divided in differents scripts :
- [suppression.sql](suppression.sql) : Delete the tables
- [base.sql](base.sql) : Create the tables
- [remplissage.sql](remplissage.sql) : Fill the tables with data
- [procedures.sql](procedures.sql) : Create procedures used in database management
- [triggers.sql](triggers.sql) : Create triggers to maintain database consistency

A typical use in MySQL shell to initialize the database is :
```sql
create database database_name
use database_name; 
source suppression.sql; 
source base.sql; 
source remplissage.sql; 
source procedures.sql; 
source triggers.sql;
```
*To modify MySQL accesses such as database name or password, you need to modify ``const connection`` in [app.js](backend/src/app.js).*

## Database Deployment
To deploy the database after its initialization, the following commands needs to be executed in the [backend](backend) and [frontend](frontend) repositories:
- ``` npm install ```
- ``` npm run serve ```

