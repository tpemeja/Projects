# P2P file sharing
Project realized in 2020 with Otavio FLORES JACOBI, Abdelouahab LAAROUSSI, Julien MIENS, Maxime ROSAY.

[Rapport_RE203.pdf](Rapport_RE203.pdf) is a French report of this project describing more precisely the work done and explained below.

## Project description

This project is the realization of a peer-to-peer file sharing system using a tracker to centralize information and indicate to peers which other peers to contact to obtain files.

The project was divided into two main parts:
- A tracker that receives requests from peers and stores the information
- Peers communicating first with the tracker, and then with other peers

## Tracker
This tracker has been realized in **C** with Maxime ROSAY.

#### In [tracker](src/tracker) directory :

``` make ```  : compile the tracker

``` ./tracker -v -p 8090 ``` : run the tracker on port 8090 ( specified by ```-p``` ) with logs ( ```-v``` )

## Peer
The peers have been realized in **Java** by Otavio FLORES JACOBI, Abdelouahab LAAROUSSI, Julien MIENS.

Default configuration defined in [config.ini](src/peer/config.ini) runs the peer with a tracker set to ```127.0.0.1:8090```.

#### In [peer](src/peer) directory :

``` make ```  : compile the peer files

```make run1``` and ```make run2``` run two peers with different files and IP addresses.
