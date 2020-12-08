while True:
    try:
        x = input ("Enter the first number: ")
        y = input ("Enter the second number: ")
        value = int(x)/int(y)
        print ('x/y is ', value)
    except Exception as e:
        print ('Invalid input: ', e)
        print ('Please retry')
    else:
        break
