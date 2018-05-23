#!/usr/bin/env python

class State(object):
    """
    We define a state object which provides some utility functions for the
    individual states within the state machine.
    """

    def __init__(self):
        print 'Processing current state:', str(self)

    def on_event(self, event):
        """
        Handle events that are delegated to this State.
        """
        pass

    def __repr__(self):
        """
        Leverages the __str__ method to describe the State.
        """
        return self.__str__()

    def __str__(self):
        """
        Returns the name of the State.
        """
        return self.__class__.__name__


class LockedState(State):
    """
    The state which indicates that there are limited device capabilities.
    """

    def on_event(self, event):
        if event == 'pin_entered':
            return UnlockedState()

        print ("I don't understand event: %s, skipping!" % event)
        return self


class UnlockedState(State):
    """
    The state which indicates that there are no limitations on device
    capabilities.
    """

    def on_event(self, event):
        if event == 'device_locked':
            return LockedState()

        print ("I don't understand event: %s, skipping!" % event)
        return self


class SimpleDevice(object):
    """ 
    A simple state machine that mimics the functionality of a device from a 
    high level.
    """

    def __init__(self):
        """ Initialize the components. """

        # Start with a default state.
        self.state = LockedState()

    def on_event(self, event):
        """
        This is the bread and butter of the state machine. Incoming events are
        delegated to the given states which then handle the event. The result is
        then assigned as the new state.
        """

        # The next state will be the result of the on_event function.
        self.state = self.state.on_event(event)

if __name__ == "__main__":
    s = SimpleDevice()
    print (s.state)
    s.on_event("pin_entered")
    print (s.state)
    s.on_event("pin_entered")
    print (s.state)
    if isinstance (s.state, UnlockedState):
        print ("Device is unlocked, trying to lock it")
        s.on_event("device_locked")
        print (s.state)
    elif isinstance (s.state, LockedState):
        print ("Device is already locked")

    s.on_event("what")
    print (s.state)

