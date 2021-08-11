/*
Copyright © 2021 Ci4Rail GmbH
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef _OTA_UPDATE_H_
#define _OTA_UPDATE_H_

void get_url_and_do_update(const int sock);

void get_sha256_of_partitions(void);

void check_current_partition(void);

void initialize_nvs(void);

#endif //_OTA_UPDATE_H_
