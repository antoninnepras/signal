# SIGNAL
Program, that generates double type numeric signal to stdout.

![screenshot.png](screenshot.png)
### options
- ***-h*** print help
- ***-t [type name]*** select signal type (square default)
  - square
  - triangle
  - saw
  - sin
- ***-r [unsigned]*** fourier series resolution (when used)
- ***-l [unsigneld]*** length of the signal (number of samples)
- ***-T [double]*** time between signals are sent in seconds
- ***-s [double]*** output x scale
- ***-a [double]*** output y scale (amplitude)
- ***-e [double]*** multiply output by exp(e)

## compile
```
make 
```

## install
```
sudo make install
```

or

```
doas make install
```

## uninstall
```
sudo make uninstall
```

or

```
doas make uninstall
```

## use 
```
signal [options]
```


