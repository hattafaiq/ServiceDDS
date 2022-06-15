float rmsf_ku(float *masuk, int jum)
{
    int i;
    float temp=0;
    for (i=0; i<jum; i++)
    {
            temp = temp + (masuk[i] * masuk[i]);
    }
    temp = (float) (temp/jum);

    //temp = sqrtf(temp);
    temp = sqrt(temp);
    return temp;
}
