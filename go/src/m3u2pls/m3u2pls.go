package main

import (
    "os"
    "fmt"
    "strings"
    "path/filepath"
    "strconv"
    "log"
    "io/ioutil"
)

func main () {
    if len(os.Args) == 1 || !strings.HasSuffix(os.Args[1], ".m3u") {
        fmt.Printf ("usage %s <file.m3u>\n", filepath.Base (os.Args[0]))
        os.Exit (1)
    }

    if rawBytes, err := ioutil.ReadFile(os.Args[1]); err != nil {
        log.Fatal (err)
    } else {
        songs := readM3uPlaylist (string(rawBytes))
        writePlsPlaylist (songs)
    }
}


type Song struct {
    Title   string
    Filename    string
    Seconds int
}

func readM3uPlaylist (data string) (songs []Song) {
    var song Song
    for _, line := range strings.Split (data, "\n") {
        line = strings.TrimSpace (line)
        if line == "" || strings.HasPrefix (line, "#EXTM3U") {
            continue
        }

        if strings.HasPrefix (line, "#EXTINF:") {
            song.Title, song.Seconds = parseExtinfLine(line)
        } else {
            song.Filename = strings.Map (mapPlatformDirSeparator, line)
        }

        if song.Filename != "" && song.Title != "" && song.Seconds != 0 {
            songs = append (songs, song)
            song = Song{}
        }
    }
    return songs
}


func parseExtinfLine (line string) (title string, seconds int) {
    if i := strings.IndexAny (line, "-0123456789"); i > -1 {
        const separator = ","
        line = line[i:]
        if j := strings.Index (line, separator); j > -1 {
            title = line[j + len(separator):]
            var err error
            if seconds, err = strconv.Atoi (line[:j]); err != nil {
                log.Printf ("faialed to read the duration for '%s': %v\n", title, err)
                seconds = -1
            }
        }
    }
    return title, seconds
}

func mapPlatformDirSeparator (char rune) rune {
    if char == '/' || char == '\\' {
        return filepath.Separator
    }
    return char
}

func writePlsPlaylist (songs []Song) {
    fmt.Println ("[playlist]")
    for i, song := range songs {
        i++
        fmt.Printf ("File%d=%s\n", i, song.Filename)
        fmt.Printf ("Title%d=%s\n", i, song.Title)
        fmt.Printf ("Length%d=%d\n", i, song.Seconds)
    }

    fmt.Printf ("NumberOfEntries=%d\nVersion=2\n", len(songs))
}
