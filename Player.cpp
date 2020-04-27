/*********************************************************************
    Player.cpp
    Group 5: Iyesha Gonzalez, Markee Davis, LeVictoria Jackosn, James Peterson
    Date Last Edited: 4/26/2020
    Purpose: read in songs and playlists from a file and be able to add to a playlist,
            delete from a playlist, add a new playlist, merge a playlist, and intersect a playlist.
********************************************************************/

#include <iostream>
#include <iomanip>
#include <cmath>
#include "StringHelper.h"
#include <string>
#include <vector>
#include "Song.h"
#include "Playlist.h"
using namespace std;

//driver menu of program
int main()
{
    
    int decision, decision2;
    string decision3;
    //Print the header
    cout << endl << setfill('-') << setw(10) << "" << "WELCOME to the AutoPlayer" << setw(10) << "" << endl;
    vector<string> names;
    string temp;
    ifstream inFile;
    ifstream inFile2;
    ofstream onFile;
    ofstream onFile2;
    inFile.open("Playlist.list");
    string x = ".playlist";
    
    Song obj;
    
    //Program Main Start
    do
    {
        //Reset decision and create test8 Playlist
        decision = 0;
        
        Playlist playlist, test10;   
        
        //Read in all of the playlist names 
        while(inFile.good())
            {
                getline(inFile, temp);
                names.push_back(temp);
            }

        //Print Main Menu and obtain users choice
        cout << endl << "You currently have " << names.size() << " playlist(s)." << endl;
  
        while((decision != 1) && (decision != 2) && (decision != 3))
            {
                cout << "1 - Open an exisiting playlist" << endl;
                cout << "2 - Create new list" << endl;
                cout << "3 - Exit" << endl;
                cout << "Selection: ";
                cin  >> decision;
            }
        
        if(decision == 2) //Opt 2 Main Menu
            {
                //reset decision and obtain users selection from the menu
                decision2 = 0;
                while((decision2 != 1) && (decision2 != 2) && (decision2 != 3))
                    {
                        cout << endl << "1 - Create new empty list";
                        cout << endl << "2 - Merge 2 exisitng playlists";
                        cout << endl << "3 - Intersect 2 exisinting playlists" << endl;
                        cout << "Selection: ";
                        cin  >> decision2;
                    }
            
            //carry out the users will
            if (decision2 == 1) //If user selects 1, then it goes here
                {
                    //first get the name of the new playlist and add it to the list
                    string newPlaylist;
                    decision3 = "";
                    cout<<endl;
                    cout << "Name of new playlist (cannot contain underscores): ";
                    cin.ignore();
                    getline(cin, newPlaylist);
                    names.push_back(newPlaylist);
                    onFile.open("Playlist.list", ios::app);
                    onFile << endl << newPlaylist;
                    decision2 = names.size();
                
                    //Go to playlist menu
                    //I did try to make this a function because it is used consistently 
                    //throughout the next two decisions, but the compiler will not let stand
                    //despite the prototype, declaration, and definition parameters being the same
                    while(decision3 != "Q")
                        {
                            //options on what to do with playlist
                            do
                                {
                                    cout<<endl;
                                    cout << "You are now playing: " << names[(decision2-1)] << endl;
                                    cout << setfill(' ') << setw(8) << "" << "A - Add a song" << endl;
                                    cout << setfill(' ') << setw(8) << "" << "D - Delete a song" << endl;
                                    cout << setfill(' ') << setw(8) << "" << "P - Play a song" << endl;
                                    cout << setfill(' ') << setw(8) << "" << "M - Set the mode" << endl;
                                    cout << setfill(' ') << setw(8) << "" << "S - Show all songs" << endl;
                                    cout << setfill(' ') << setw(8) << "" << "Q - Quit";
                                    cout << "\nSelection: ";
                                    cin  >> decision3;
                                    decision3 = StringHelper::toUpper(decision3);
                                }
                    while((decision3 != "A") && (decision3 != "D") && (decision3 != "P") && (decision3 != "M")
                    && (decision3 != "S") && (decision3 != "Q"));

                    //Set mode decision3
                    if (decision3 == "A") //Add a song
                        {
                            onFile2.open((newPlaylist + x).c_str(), ios::app); //open file for the playlist that was created
                            cin  >> obj;
                            playlist.addSong(obj);
                            onFile2 << obj;
                            onFile2.close();
                        }

                    if (decision3 == "D") //Delete a song
                        {
                            onFile2.open((newPlaylist + x).c_str()); //Open file for new playlist made
                            string title, artist;                 //but so that it rewrites the file
                            cin.ignore();
                            cout << "Title: ";
                            getline(cin, title);
                            cout << "Artist: ";
                            getline(cin, artist);
                            Song test9(title, artist, "Don't matter", 0, 0);
                            playlist = playlist - test9;   
                            onFile2 << playlist;
                            onFile2.close();
                        }

                    if (decision3 == "P") //Play a song
                        {
                            playlist.play();
                        }

                    if (decision3 == "M") //Set the mode
                    {
                        string mode = "";
                        while((mode != "N") && (mode != "R") && (mode != "L"))
                            {
                                cout << "Enter mode: \n"; 
                                cout << setfill(' ') << setw(8) << "" << "N - Normal" << endl;
                                cout << setfill(' ') << setw(8) << "" << "R - Repeat" << endl;
                                cout << setfill(' ') << setw(8) << "" << "L - Loop" << endl;
                                cout << "Selection: ";
                                cin  >> mode;
                                mode = StringHelper::toUpper(mode);
                            }


                        Playlist::setMode(mode);
                        cout << "Mode is now " << mode << endl;
                    }


                    if (decision3 == "S") //Show all the songs
                        {
                            cout << playlist;
                        }                
                }
                
            }
            
            if(decision2 == 2)//If user selects 2, then it goes here
                {
                    //first get the name of the new playlist and add it to the list
                    string newPlaylist;
                    decision3 = "";
                    Playlist test11, test12; //create two playlist objects that will merge 
                    cout << "Name of new playlist (cannot contain underscores): ";
                    cin.ignore();
                    getline(cin, newPlaylist);
                    names.push_back(newPlaylist);
                    onFile.open("Playlist.list", ios::app);
                    onFile << endl << newPlaylist;
                
                    //Then print out the playlists and get the users input for list merging
                    cout << "Which of the following playlists would like to merge?" << endl; 
                    for(int i = 0; i < (names.size() - 1); i++)
                        {
                            cout << (i + 1) << " " << names[i] << endl;
                        }
                
                    //get the users first playlist selection
                    do
                        {
                            cout << "Playlist 1: ";
                            cin >> decision;
                            if((decision > (names.size() - 1)) || (decision == 0))
                            cout << "Invalid selection";
                        }
                    while ((decision > (names.size() - 1)) || (decision == 0));

                        //open the playlist that the user chose and load in the songs
                        inFile2.open((names[(decision - 1)] + x).c_str());                
                        while(inFile2.good())
                        {
                            Song brandNew;
                            inFile2 >> brandNew;
                            test11.addSong(brandNew);
                        }
                    //make sure to close the file so that you can read in if needed again
                    inFile2.close(); 
                
                    //this will get the users second selected playlist          
                    do
                        {
                            cout << "\nPlaylist 2: ";
                            cin >> decision2;
                            if((decision2 > (names.size() - 1)) || (decision2 == 0))
                            cout << "Invalid selection";
                        }
                    while ((decision2 > (names.size() - 1)) || (decision2 == 0));

                        //open the playlist that the user chose and load in the songs
                        inFile2.open((names[(decision2 - 1)] + x).c_str());
                    while(inFile2.good())
                        {
                            Song brandNew;
                            inFile2 >> brandNew;
                            test12.addSong(brandNew);
                         }
                    //make sure to close the file so that you can read in if needed again
                    inFile2.close(); 
                    
                    //will merge both playlists
                   playlist = test11 + test12;
                
                    //open file for the playlist that was created
                    onFile2.open((newPlaylist + x).c_str(), ios::app); 
                    //print all songs to new file
                    onFile2 << playlist;
                    onFile2.close();
                    //Go to playlist menu
                    while(decision3 != "Q")
                        {
                    
                         //options with playlist
                        do
                            {
                                cout<<endl;
                                cout << "You are now playing: " << names[(names.size() - 1)] << endl;
                                cout << setfill(' ') << setw(8) << "" << "A - Add a song" << endl;
                                cout << setfill(' ') << setw(8) << "" << "D - Delete a song" << endl;
                                cout << setfill(' ') << setw(8) << "" << "P - Play a song" << endl;
                                cout << setfill(' ') << setw(8) << "" << "M - Set the mode" << endl;
                                cout << setfill(' ') << setw(8) << "" << "S - Show all songs" << endl;
                                cout << setfill(' ') << setw(8) << "" << "Q - Quit";
                                cout << "\nSelection: ";
                                cin >> decision3;
                                decision3 = StringHelper::toUpper(decision3);
                            }
                        while((decision3 != "A") && (decision3 != "D") && (decision3 != "P") && (decision3 != "M")
                          && (decision3 != "S") && (decision3 != "Q"));


                        //Set mode to decision3
                        if (decision3 == "A") //Add a song
                            {
                                onFile2.open((newPlaylist + x).c_str(), ios::app); //open file for the playlist that was created
                                cin >> obj;
                                playlist.addSong(obj);
                                onFile2 <<obj;
                                onFile2.close();
                            }

                    if (decision3 == "D") //Delete a song
                    {
                        string title, artist;
                        onFile2.open((newPlaylist + x).c_str());
                        cin.ignore();
                        cout << "Title: ";
                        getline(cin, title);
                        cout << "Artist: ";
                        getline(cin, artist);
                        Song test9(title, artist, "Don't matter", 0, 0);
                        playlist = playlist - test9;   
                        onFile2 << playlist;
                        onFile2.close();
                        
                    }

                    if (decision3 == "P") //Play a song
                    {
                        playlist.play();
                    }

                    if (decision3 == "M") //Set the mode
                    {
                        string mode = "";
                        while((mode != "N") && (mode != "R") && (mode != "L"))
                        {
                            cout << "Enter mode: \n"; 
                            cout << setfill(' ') << setw(8) << "" << "N - Normal" << endl;
                            cout << setfill(' ') << setw(8) << "" << "R - Repeat" << endl;
                            cout << setfill(' ') << setw(8) << "" << "L - Loop" << endl;
                            cout << "Selection: ";
                            cin >> mode;
                            mode = StringHelper::toUpper(mode);
                        }


                        Playlist::setMode(mode);
                        cout << "Mode is now " << mode << endl;
                    }


                    if (decision3 == "S") //Show all the songs
                    {
                        cout << playlist;
                    }                
                }
                
                //clear the lists for the next use
                test11.clearList();
                test12.clearList();
                
            }
            
            if(decision2 == 3)//If user selects 3, then it goes here
            {
                //first get the name of the new playlist and add it to the list
                string newPlaylist;
                decision3 = "";
                Playlist test11, test12; //create two playlist objects that will merge 
                cout << "Name of new playlist (cannot contain underscores): ";
                cin.ignore();
                getline(cin, newPlaylist);
                names.push_back(newPlaylist);
                onFile.open("Playlist.list", ios::app);
                onFile << endl << newPlaylist;
                
                //Then print out the playlists and get the users input for list merging
                cout << "Which of the following playlists would like to intersect?" << endl; 
                for(int i = 0; i < (names.size() - 1); i++)
                {
                    cout << (i + 1) << " " << names[i] << endl;
                }
                
                //user selects first playlist
                do
                {
                    cout << "Playlist 1: ";
                    cin >> decision;
                    if((decision > (names.size() - 1)) || (decision == 0))
                        cout << "Invalid selection";
                }while ((decision > (names.size() - 1)) || (decision == 0));

                //open the playlist that the user chose and load in the songs
                inFile2.open((names[(decision - 1)] + x).c_str());
                
                //read in the songs
                while(inFile2.good())
                    {
                        Song brandNew;
                        inFile2 >> brandNew;
                        test11.addSong(brandNew);
                    }
                //make sure to close the file 
                inFile2.close(); 
                
                //add first playlist to what will be th emain playlist
                playlist = playlist + test11;
                
                //get users second selected playlist
                do
                {
                    cout << "\nPlaylist 2: ";
                    cin >> decision2;
                    if((decision2 > (names.size() - 1)) || (decision2 == 0))
                        cout << "Invalid selection";
                }while ((decision2 > (names.size() - 1)) || (decision2 == 0));

                //open the playlist that the user chose and load in the songs
                inFile2.open((names[(decision2 - 1)] + x).c_str());
                while(inFile2.good())
                    {
                        Song brandNew;
                        inFile2 >> brandNew;
                        test12.addSong(brandNew);
                    }
                //make sure to close the file so that you can read in if needed again
                inFile2.close();
                
                //This will return the intersected playlist of the selected two
                playlist = playlist.intersect(test12);
                
                onFile2.open((newPlaylist + x).c_str(), ios::app); //open file for the playlist that was created
                //print all the songs to the new file
                onFile2 << playlist;
                onFile2.close();
                
                //Go to playlist menu
                while(decision3 != "Q")
                {
                    //options on what to do with playlist
                    do
                    {
                        cout<<endl;
                        cout << "You are now playing: " << names[(names.size() - 1)] << endl;
                        cout << setfill(' ') << setw(8) << "" << "A - Add a song" << endl;
                        cout << setfill(' ') << setw(8) << "" << "D - Delete a song" << endl;
                        cout << setfill(' ') << setw(8) << "" << "P - Play a song" << endl;
                        cout << setfill(' ') << setw(8) << "" << "M - Set the mode" << endl;
                        cout << setfill(' ') << setw(8) << "" << "S - Show all songs" << endl;
                        cout << setfill(' ') << setw(8) << "" << "Q - Quit";
                        cout << "\nSelection: ";
                        cin >> decision3;
                        decision3 = StringHelper::toUpper(decision3);
                    }while((decision3 != "A") && (decision3 != "D") && (decision3 != "P") && (decision3 != "M")
                          && (decision3 != "S") && (decision3 != "Q"));


                    //Set mode decision3
                    if (decision3 == "A") //Add a song
                    {
                        onFile2.open((newPlaylist + x).c_str(), ios::app); //open file for the playlist that was created
                        cin >> obj;
                        playlist.addSong(obj);
                        onFile2 << obj;
                        onFile2.close();
                    }

                    if (decision3 == "D") //Delete a song
                    {
                        string title, artist;
                        onFile2.open((newPlaylist + x).c_str());
                        cin.ignore();
                        cout << "Title: ";
                        getline(cin, title);
                        cout << "Artist: ";
                        getline(cin, artist);
                        Song test9(title, artist, "Don't matter", 0, 0);
                        playlist = playlist - test9;   
                        onFile2 << playlist;
                        onFile2.close();                
                    }

                    if (decision3 == "P") //Play a song
                    {
                        playlist.play();
                    }

                    if (decision3 == "M") //Set the mode
                    {
                        string mode = "";
                        while((mode != "N") && (mode != "R") && (mode != "L"))
                        {
                            cout << "Enter mode: \n"; 
                            cout << setfill(' ') << setw(8) << "" << "N - Normal" << endl;
                            cout << setfill(' ') << setw(8) << "" << "R - Repeat" << endl;
                            cout << setfill(' ') << setw(8) << "" << "L - Loop" << endl;
                            cout << "Selection: ";
                            cin >> mode;
                            mode = StringHelper::toUpper(mode);
                        }


                        Playlist::setMode(mode);
                        cout << "Mode is now " << mode << endl;
                    }


                    if (decision3 == "S") //Show all the songs
                    {
                        cout << playlist;
                    }                
                }
                
                //clear the lists for the next use
                test11.clearList();
                test12.clearList();
                
            } 
           
        }
        else if(decision == 1) //OPTION NUMBER 1 FROM MAIN MENU
        {
            //SELECT  PLAYLIST and reset decision3
            decision3 = "";
            cout << "Please select a playlist from below:" << endl; 
            for(int i = 0; i < names.size(); i++)
            {
                cout << (i+1) << " " << names[i] << endl;
            }
            
            
            //Get user decision with error checking
            do
            {
                cout << "Selection: ";
                cin >> decision2;
                if((decision2 > names.size()) || (decision2 == 0))
                    cout << "Invalid selection";
            }while ((decision2 > names.size()) || (decision2 == 0));
            
            
            
            
            
            
            
//             playlistMenu(inF2, decision2, decision3, test8, test7, names, x);
            
                        
            while(decision3 != "Q")
            {
                //options on what to do with playlist
                do
                {
                    cout<<endl;
                    cout << "You are now playing: " << names[(decision2 - 1)] << endl;
                    cout << setfill(' ') << setw(8) << "" << "A - Add a song" << endl;
                    cout << setfill(' ') << setw(8) << "" << "D - Delete a song" << endl;
                    cout << setfill(' ') << setw(8) << "" << "P - Play a song" << endl;
                    cout << setfill(' ') << setw(8) << "" << "M - Set the mode" << endl;
                    cout << setfill(' ') << setw(8) << "" << "S - Show all songs" << endl;
                    cout << setfill(' ') << setw(8) << "" << "Q - Quit";
                    cout << "\nSelection: ";
                    cin >> decision3;
                    decision3 = StringHelper::toUpper(decision3);
                }while((decision3 != "A") && (decision3 != "D") && (decision3 != "P") && (decision3 != "M")
                      && (decision3 != "S") && (decision3 != "Q"));


               
                if (decision3 == "A") //Add a song
                {
                    onFile2.open((names[(decision2 - 1)] + x).c_str(), ios::app); //open file for the playlist that was opened
                    cin >> obj;
                    playlist.addSong(obj);
                    onFile2 << obj;
                    onFile2.close();
                }
                
                if (decision3 == "D") //Delete a song
                {
                    onFile2.open((names[(decision2 - 1)] + x).c_str()); //open file for the playlist that was opened
                    string title, artist;                          //but so that it rewrites the file
                    cin.ignore();
                    cout << "Title: ";
                    getline(cin, title);
                    cout << "Artist: ";
                    getline(cin, artist);
                    Song test9(title, artist, "Don't matter", 0, 0);
                    playlist = playlist - test9;   
                    onFile2 << playlist;
                    onFile2.close();
                }
                
                if (decision3 == "P") //Play a song
                {
                    playlist.play();
                }
                
                if (decision3 == "M") //Set the mode
                {
                    string mode = "";
                    while((mode != "N") && (mode != "R") && (mode != "L"))
                    {
                        cout << "Enter mode: \n"; 
                        cout << setfill(' ') << setw(8) << "" << "N - Normal" << endl;
                        cout << setfill(' ') << setw(8) << "" << "R - Repeat" << endl;
                        cout << setfill(' ') << setw(8) << "" << "L - Loop" << endl;
                        cout << "Selection: ";
                        cin >> mode;
                        mode = StringHelper::toUpper(mode);
                    }


                    Playlist::setMode(mode);
                    cout << "Mode is now " << mode << endl;
                }

                
                if (decision3 == "S") //Show all the songs
                {
                    cout << playlist;
                }                
            }
            
            
            
        }
        
        //clear the playlist for next use if needed
        playlist.clearList();
        
        
    }while (decision != 3); //End the program if the user enters a 3 which is quit, otherwise continue 


    return 0;
}

