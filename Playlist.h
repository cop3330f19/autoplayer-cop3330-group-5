/*********************************************************************
    Playlist.h
    Group 5: Iyesha Gonzalez, Markee Davis, LeVictoria Jackosn, James Peterson
    Date Last Edited: 4/26/2020
    Purpose: Sets the playlist class and its functions
********************************************************************/


#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>


class Playlist
{
    private:
        int sizeOfVect;
        std::vector<Song> songList;
        static std::string mode; //static mode so it persists across all playlists
        static int playCount; //static playCount to keep track of location in playlist
        
        
        
    public:
        Playlist();
        
     /**************************************************************
	 *                 Playlist operator+                         *
	 *                                                            *
	 * Passed   : 2 arguments: Playlist and Song object           *
	 * Purpose  : Adds song to the Playlist object                *
	 * Returns  : Playlist object                                 *
	 **************************************************************/
        friend Playlist operator+(Playlist& lhs, Song& rhs);
        
     /**************************************************************
	 *                 Playlist operator+                         *
	 *                                                            *
	 * Passed   : 2 arguments: Playlist and Playlist object       *
	 * Purpose  : Merges two Playlist objects                     *
	 * Returns  : Playlist object                                 *
	 **************************************************************/
        friend Playlist operator+(Playlist& lhs, Playlist& rhs);
        
     /**************************************************************
	 *                 Playlist operator-                         *
	 *                                                            *
	 * Passed   : 2 arguments: Playlist and Song object           *
	 * Purpose  : Deletes song from the Playlist object           *
	 * Returns  : Playlist object                                 *
	 **************************************************************/
        friend Playlist operator-(Playlist& lhs, Song& rhs);
        
        
     /**************************************************************
	 *                 ostream operator<<                         *
	 *                                                            *
	 * Passed   : 2 arguments: ostream and Playlist object        *
	 * Purpose  : Outputs Playlist songs to Console               *
	 * Returns  : ostream                                         *
	 **************************************************************/
        friend std::ostream& operator<<(std::ostream& os, const Playlist& prnt);
        
     /**************************************************************
	 *                 ostream operator<<                         *
	 *                                                            *
	 * Passed   : 2 arguments: ostream and Playlist object        *
	 * Purpose  : Prints Playlist songs to file                   *
	 * Returns  : ostream                                         *
	 **************************************************************/
        friend std::ofstream& operator<<(std::ofstream& os, const Playlist& prnt);
        
     /**************************************************************
	 *                       addSong                              *
	 *                                                            *
	 * Passed   : 1 argument: Song object                         *
	 * Purpose  : Adds song to the Playlist object                *
	 * Returns  : none                                            *
	 **************************************************************/  
        void addSong(Song);
        
     /**************************************************************
	 *                       deleteSong                           *
	 *                                                            *
	 * Passed   : 1 argument: Song object                         *
	 * Purpose  : Deletes song from the Playlist object           *
	 * Returns  : none                                            *
	 **************************************************************/
        void deleteSong(Song);
      
     /**************************************************************
	 *                       Playlist intersect                   *
	 *                                                            *
	 * Passed   : 1 argument: Playlist object                     *
	 * Purpose  : Intersects two Playlist objects                 *
	 * Returns  : Playlist Object                                 *
	 **************************************************************/
        Playlist intersect(Playlist&);
     
     /**************************************************************
	 *                       play                                 *
	 *                                                            *
	 * Passed   : 0 argument: none                                *
	 * Purpose  : Plays a song from the Playlist object           *
	 * Returns  : none                                            *
	 **************************************************************/
        void play();
        
     /**************************************************************
	 *                       clearList                            *
	 *                                                            *
	 * Passed   : 0 argument: none                                *
	 * Purpose  : Clears Playlist                                 *
	 * Returns  : none                                            *
	 **************************************************************/
        void clearList();
        
     /**************************************************************
	 *                       setMode                              *
	 *                                                            *
	 * Passed   : 1 argument: String                              *
	 * Purpose  : Changes the mode of the player                  *
	 * Returns  : none                                            *
	 **************************************************************/
        static void setMode(std::string);
 
    
};
#endif

