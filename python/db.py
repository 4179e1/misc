import sys, shelve

if sys.version > '3':
    myinput = input
else:
    myinput = raw_input

def store_person (db):
    pid = myinput('Enter unique ID number: ')
    person = {}
    person['name'] = myinput('Enter name: ')
    person['age'] = myinput('Enter age: ')
    person['phone'] =myinput('Enter phone number: ')
    db[pid]=person

def lookup_person (db):
    pid = myinput('Enter ID number: ')
    field = myinput('What would you like to know? (name, age, phone)' )
    field = field.strip().lower()
    print (field.capitalize() + ':', db[pid][field])

def print_help ():
    print ('The available commands are:')
    print ('store   : Store information about a person')
    print ('lookup  : Looks up a person from ID number')
    print ('quit    : Save changes and exit')
    print ('?       : Prints this message')

def enter_command():
    cmd = myinput ('Enter command (? for help:): ')
    cmd = cmd.strip().lower()
    return cmd

def main():
    database = shelve.open('test.db')
    try:
        while True:
            cmd = enter_command()
            if cmd == 'store':
                store_person (database)
            elif cmd == 'lookup':
                lookup_person (database)
            elif cmd == '?':
                print_help()
            elif cmd == 'quit':
                return
    finally:
        database.close()

if __name__ == '__main__':
    main()

