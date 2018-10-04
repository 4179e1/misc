import sys
import logging

#This function should be called from the main thread before other threads are started. 

#logging.basicConfig (filename="example.log", filemode='w', level=logging.DEBUG)
logging.basicConfig (steam=sys.stderr, format='%(asctime)s %(message)s', datefmt='%m/%d/%Y %I:%M:%S', level=logging.DEBUG)
logging.debug ('This message should go to the log file')
logging.info ('So should this')
logging.warning('And this, too')
