package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"path/filepath"
	"strings"
)

const (
	ERR_NO_ARGS = iota
	ERR_FILE_NOT_FOUND
	ERR_WRONG_EXT

	VERSION      = "1.0"
	EXTENSION    = ".lstr"
	PROGRAM_NAME = "lister"
	AUTHOR       = "Laurentino Luna"
)

func throwError(errcode int) {
	switch errcode {
	case ERR_NO_ARGS:
		usage()
		break
	case ERR_FILE_NOT_FOUND:
		fmt.Printf("%v: file not found\n", PROGRAM_NAME)
		break
	case ERR_WRONG_EXT:
		fmt.Printf("%v: wrong extension. Need %v\n", PROGRAM_NAME, EXTENSION)
	}
}

func usage() {
	fmt.Printf("%v - checklist\n", PROGRAM_NAME)
	fmt.Printf("./%v <LISTER_FILE>\n", PROGRAM_NAME)
}

func version() {
	fmt.Printf("%v %v\nWritten by %v\n", PROGRAM_NAME, VERSION, AUTHOR)
}

func readLines(f *os.File) []string {
	result := []string{}
	scanner := bufio.NewScanner(f)

	for scanner.Scan() {
		result = append(result, scanner.Text())
	}

	return result
}

func main() {
	flagVersion := flag.Bool("v", false, "output version")
	argFile := flag.String("file", "default.lstr", "file to check")
	checkedCount := 0
	elementCount := 0

	flag.Parse()

	args := os.Args
	if len(args) < 2 {
		throwError(ERR_NO_ARGS)
		os.Exit(1)
	} else if len(args) == 2 {
		*argFile = args[1]
	}

	if *flagVersion {
		version()
		os.Exit(0)
	}

	// Read the file

	// ... but first check the extension
	ext := filepath.Ext(*argFile)
	if ext != EXTENSION {
		throwError(ERR_WRONG_EXT)
		os.Exit(1)
	}

	f, err := os.Open(*argFile)
	if err != nil {
		throwError(ERR_FILE_NOT_FOUND)
		os.Exit(1)
	}
	defer f.Close()

	lines := readLines(f)
	fmt.Println(lines[0])
	for i := 0; i < len(lines[0]); i++ {
		fmt.Printf("=")
	}
	fmt.Println()

	for i := 1; i < len(lines); i++ {
		// Parse each line
		line := lines[i]
		if strings.HasPrefix(line, "x") {
			fmt.Printf("[x] - %v\n", line[2:])
			checkedCount++
		} else if strings.HasPrefix(line, "?") {
			fmt.Printf("[TBD] - %v\n", line[2:])
		} else {
			if len(line) != 0 {
				fmt.Printf("[] - %v\n", line)
			}
		}

		if len(line) != 0 {
			elementCount++
		}
	}
	for i := 0; i < len(lines[0]); i++ {
		fmt.Printf("=")
	}
	fmt.Println()

	// Display information
	fmt.Printf("\nTotal elements: %v\nChecked: %v\n", elementCount, checkedCount)
}
