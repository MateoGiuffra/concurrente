class Buffer {
    private Object[] data;
    private int begin;
    private int end;
    private int n;

    public Buffer(int N){
        this.data = new Object[N+1];
        this.begin = 0;
        this.n = N;
        this.end = 0;
    }

    public synchronized void write(Object o) throws InterruptedException {
        while (isFull()) wait();
        data[begin] = o;
        begin = next(begin);
        notifyAll();
    }

    public synchronized Object read() throws InterruptedException {
        while (isEmpty()) wait();
        Object result = data[end];
        end = next(end);
        notifyAll();
        return result;
    }

    private boolean isEmpty() { return begin == end; }
    private boolean isFull() { return next(begin) ==  end; }
    private int next(int i) { return (i+1) % (this.n+1); }

}