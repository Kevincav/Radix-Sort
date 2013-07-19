#ifndef _SCOTTGS_TIMING_H_
#define _SCOTTGS_TIMING_H_

namespace scottgs
{

///
/// This class acts as a stop watch to allow for the timing of code sections
/// Written by Matt Klaric
///
class Timing
{

    public:
    
        ///
        /// Create a timing object in the stopped state.
        ///
        Timing();
        
        ///
        /// Start the timer
        ///
        void start();
        
        ///
        /// Stop the timing on the current split, but keep the timer running
        ///
        void split();
        
        ///
        /// Stop the timing completely
        ///
        void stop();
        
        ///
        /// Reset the timer completely
        ///
        void reset();
        
        ///
        /// Get the total elasped time since the start method was called (after
        /// the object was created or reset)
        ///
        double getTotalElapsedTime() const;
        
        ///
        /// Get the time elapsed since the split method was called last (or
        /// the start method was called if split has never been called).
        ///
        double getSplitElapsedTime() const;
        
        ///
        /// Simply return the current time as a double.  This method can be called
        /// at any point, even if the timer object is currently stopped.
        ///
        double getCurrentTime() const;
        
    private:
    
        ///
        /// Tracks whether or not the timer is currently running
        ///
        bool _isRunning;
        
        ///
        /// Track the time that the start() method was called or a new split was begun
        ///
        double _startingTime;
        
        ///
        /// Track the total time of all of the splits
        ///
        double _elapsedTime;
        
        ///
        /// Used by the constructor and the reset method
        ///
        void init();
};

}; // namespace scottgs

#endif
