/*********************************************************************
    Playlist.cpp
    Group 5: Iyesha Gonzalez, Markee Davis, LeVictoria Jackosn, James Peterson
    Date Last Edited: 4/26/2020
    Purpose: Defines the playlist class and defines its functions
********************************************************************/


#include "Playlist.h"
#include "StringHelper.h"
#include "Song.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

//default constructor
Playlist::Playlist()
{
    
}

//declare static variables
string Playlist::mode = "N";
int Playlist::playCount = 0;

/**************************************************************
	 *                       setMode                              *
	 *                                                            *
	 * Passed   : 1 argument: String                              *
	 * Purpose  : Changes the mode of the player                  *
	 * Returns  : none                                            *
	 **************************************************************/
void Playlist::setMode(string m)
{mode = m;}

/**************************************************************
*                       addSong                              *
*                                                            *
* Passed   : 1 argument: Song object                         *
* Purpose  : Adds song to the Playlist object                *
* Returns  : none                                            *
**************************************************************/
void Playlist::addSong(Song h)
{songList.push_back(h);}

/**************************************************************
	 *                       setMode                              *
	 *                                                            *
	 * Passed   : 1 argument: String                              *
	 * Purpose  : Changes the mode of the player                  *
	 * Returns  : none                                            *
	 **************************************************************/
void Playlist::clearList()
{songList.clear();}

/**************************************************************
	 *                       deleteSong                           *
	 *                                                            *
	 * Passed   : 1 argument: Song object                         *
	 * Purpose  : Deletes song from the Playlist object           *
	 * Returns  : none                                            *
	 **************************************************************/
void Playlist::deleteSong(Song h)
{
    int i = 0;
    bool searched, dank;
    dank = false;
    while(i < songList.size())
    {
        searched = false;
        //search for the song to be deleted, if found, set searched and dank to true
        if(songList[i] == h)
        {
            searched = true;
            dank = true;
        }
        
        //if search is true, delete that song from the list every time it is found
        if(searched == true)
        {
            songList.erase(songList.begin() + i);
        }
        
        i++; //increment counter AFTER everything has occurred
    }
    
    if(dank == true)//if dank is true or false print these messages
    {
        cout << "Song successfully deleted" << endl;
    }
    else if(dank == false)
    {
        cout << "No such song exists" << endl;
    }
}

/**************************************************************
	 *                       play                                 *
	 *                                                            *
	 * Passed   : 0 argument: none                                *
	 * Purpose  : Plays a song from the Playlist object           *
	 * Returns  : none                                            *
	 **************************************************************/
void Playlist::play()
{
    if(mode == "N" || mode== "n")//Normal mode
    {
        cout << endl << "NOW PLAYING: \n";
        if(playCount < songList.size()) //as long as playCnt is less than the songList size, play the song
        {                 
            cout << songList[playCount] << endl;
            playCount++; //increase playCnt so the next song plays next time around
        }
        else
        {
            cout << "END OF PLAYLIST\n" << endl; //print if playCnt is larger than songList
        }
    }
    
    if (mode == "R" || mode== "r")//Repeat mode
    {
        cout << endl << "NOW PLAYING: \n";
        if(playCount < songList.size())
        {
            cout << songList[playCount] << endl;
        }
        else
        {
            cout << songList[(playCount - 1)];
        }
    }
    
    if(mode == "L" || mode== "l")//Loop mode
    {
        cout << endl << "NOW PLAYING: \n";
        if(playCount < songList.size())
        {
            cout << songList[playCount] << endl;
            playCount++; //increase playCnt so the next song plays next time around
        }
        else
        {
            playCount = 0; //set playCnt to 0 so it goes to the beginning of the playlist
            cout << songList[playCount] << endl; //play the first song again
            playCount++; //increment playCnt so that the first song doesn't repeat
            
        }
    }
}

/**************************************************************
	 *                       Playlist intersect                   *
	 *                                                            *
	 * Passed   : 1 argument: Playlist object                     *
	 * Purpose  : Intersects two Playlist objects                 *
	 * Returns  : Playlist Object                                 *
	 **************************************************************/
Playlist Playlist::intersect(Playlist &h)
{
    bool searched;
    int i, j, size1, size2;
    Playlist n;
    
    i = 0;
    while(i < songList.size())
    {
        j = 0;
        while(j < songList.size())
        {
            if(songList[i] == h.songList[j]) //check if the songs are the same
            {
                searched = true; //the song was found in both playlists   
                n.songList.push_back(songList[i]);
            }
            j++;
        }
        i++;
    }
    
    return n;
    
}

/**************************************************************
	 *                  operator+                                 *
	 *                                                            *
	 * Passed   : 2 arguments: Playlist and Song object           *
	 * Purpose  : Add song to playlist                            *
	 * Returns  : Playlist object                                 *
	 **************************************************************/
Playlist operator+(Playlist& lhs, Song& rhs)
{
    lhs.songList.push_back(rhs);
    return lhs;
    
}

/**************************************************************
	 *                  operator+                                 *
	 *                                                            *
	 * Passed   : 2 arguments: Playlist objects                   *
	 * Purpose  : Merge two playlists                             *
	 * Returns  : Playlist object                                 *
	 **************************************************************/
Playlist operator+(Playlist& lhs, Playlist& rhs)
{
    Playlist newOne;
    for(int i = 0; i < lhs.songList.size(); i++)
    {
        newOne.songList.push_back(lhs.songList[i]);
    }
    
    for(int i = 0; i < rhs.songList.size(); i++)
    {
        newOne.songList.push_back(rhs.songList[i]);
    }
    
    return newOne;
    
}


/**************************************************************
	 *                  operator-                                 *
	 *                                                            *
	 * Passed   : 2 arguments: Playlist and Song object           *
	 * Purpose  : Remove song from playlist                       *
	 * Returns  : Playlist object                                 *
	 **************************************************************/
Playlist operator-(Playlist& lhs, Song& rhs)
    {
        int i = 0;
        bool searched, dank; 
        dank = false; //set dank to false 
        while(i < lhs.songList.size())
            {
                searched = false;
                //search for the song to be deleted, if found, set searched and dank to true
                if(lhs.songList[i] == rhs)
            {
            searched = true;
            dank = true;
        }
        
        
        
        //if search is true, delete that song from the list every time it is found
        if(searched == true)
        {
            lhs.songList.erase(lhs.songList.begin() + i);
        }
        
        i++; //increment counter AFTER everything has occurred
        
    }
    
    if(dank == true) //if dank is true or false, print these messages
    {
        cout << "Song successfully deleted" << endl;
    }
    else if(dank == false)
    {
        cout << "No such song exists" << endl;
    }
    return lhs;
    
}

/**************************************************************
	 *                 ostream operator<<                         *
	 *                                                            *
	 * Passed   : 2 arguments: ofstream and Playlist object       *
	 * Purpose  : Print playlist to console                       *
	 * Returns  : ofstream                                        *
	 **************************************************************/
ostream& operator<<(ostream& os, const Playlist& prnt)
    {   
        for(int i = 0; i < prnt.songList.size(); i++)
        {os << prnt.songList[i] << endl;} 
        return os;
    }


/**************************************************************
	 *                 ofstream operator<<                        *
	 *                                                            *
	 * Passed   : 2 arguments: ofstream and Playlist object       *
	 * Purpose  : Print playlist to file                          *
	 * Returns  : ofstream                                        *
	 **************************************************************/
ofstream& operator<<(ofstream& os, const Playlist& prnt)
    {
        for(int i = 0; i < prnt.songList.size(); i++)
        {os << prnt.songList[i];}
    }
