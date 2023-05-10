09-05-2023 commit link 178bd52

Detail : tests made with randomly generated dataset for **single model detection** (line). 

Constants :

```
EPSILON       = 0.1
Z             = 1
SQUARED_SIGMA = 2
```

### With 0 outliers :

| Inliers     | tests pass  |
| ----------- | ----------- |
| 40          | 10/10       |
| 30          | 10/10       |
| 20          | 10/10       |
| 10          | 10/10       |


### With 10 outliers :

| Inliers     | tests pass  |
| ----------- | ----------- |
| 40          | 9/10        |
| 30          | 5/10        |
| 20          | 9/10        |


### With 20 outliers :

| Inliers     | tests pass  |
| ----------- | ----------- |
| 40          | 2/10        |


## Observation

I observed that outlier clusters sometimes contain inlier points, and we cannot merge them into the final inlier clusters. Maybe I should try to dig in the discrete distribution from `computeProbabilitiesFor` method to reduce this phenomenon.

Also, for some reasons the initial sampling causes sometimes impossible linking (each cluster's PS are disinct ??). **This needs to be checked**.

------
