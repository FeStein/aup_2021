/*  FUNKTION ZUM LOESEN EINES LINEAREN ALGEBRAISCHEN
    GLEICHUNGSSYSTEMS MIT DEM GAUSS ALGORITHMUS */

void gauss(double* m, double* x, double* r, int n)
{
    /* n - Anzahl der Zeilen bzw. Spalten des Gleichungssystems  
       x    - Loesungsvektor
       r    - rechte Seite des Gleichungssystems  */  
       
   int i, j, k;    
       
   /* ERZEUGEN EINER DREIECKSMATRIX */
   for( i = 0; i <= n - 2; i++)
   {
       for(k = i + 1; k <= n - 1; k++)
       {
           for(j = i; j <= n - 1; j++)
           {
              x[j] = -m[ i * n + j] * m[ k * n + i]/m[ i * n + i];
           }

           r[k] = r[k] - r[i] * m[ k * n + i]/m[ i * n + i];

           for(j = i; j <= n - 1; j++)
           {
              m[ k * n + j] = m[ k * n + j] + x[j];
           }
       }
   }

   /*  RUECKWAERTSEINSETZEN UM x ZU ERHALTEN  */
   x[n - 1] = r[n - 1]/m[ (n - 1) * n + n - 1];

   for(i = n - 2; i >= 0; i--)
   {
       x[i] = r[i];
       for(j = i + 1; j <= n - 1; j++)
       {
           x[i] = x[i] - m[ i * n + j] * x[j];
       }
       
       x[i] = x[i]/m[ i * n + i];
   }
   return;
}
