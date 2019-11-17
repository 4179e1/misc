try: 
    x = input ('Enter the first number: ')
    y = input ('Enter the second number: ')
    print (int(x)/int(y))
except ZeroDivisionError as e:
    print ("Zero division:", e)
except (TypeError, NameError) as e:
    print ("Type error or Name error:", e)
except Exception as e:
    print ("Something wrong happened:", e)
else:
    print ("Ah... It wen as planned.")
# always get executed
finally:
    print ("Anyway, we are done")
