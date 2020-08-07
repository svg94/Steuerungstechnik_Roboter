//*******************************************************************
class cTask_Example : public cTaskHandler::Task
{
  public:
    //---------------------------------------------------------------
    unsigned cnt;

  public:
    //---------------------------------------------------------------
    cTask_Example( cTaskHandler &taskHandler )
    
    : Task( taskHandler )
    
    {
      cnt = 0;
    }

  private:
    //---------------------------------------------------------------
    virtual void update( void )
    {
      cnt++;
    }
};
